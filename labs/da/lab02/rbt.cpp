#include "rbt.hpp"

Trbt::Trbt()
    : root(new TNode(BLACK, 0, nullptr))
    , leaf(root)
{
    // if (root != leaf)
    //     exit(1);
}

Trbt::~Trbt()
{
    if (root == leaf) {
        delete root;
        return;
    }

    if (root) {
        delete root;
        root = nullptr;
    }

    if (leaf)
        delete leaf;
    leaf = nullptr;
}

TNode::TNode(color new_clr, ull new_key, char* new_value)
    : prev(nullptr)
    , left(nullptr)
    , right(nullptr)
    , word(new_value)
    , key(new_key)
    , clr(new_clr)
{
    word = new_value;
}

TNode::~TNode()
{
    if (word)
        delete[] word;

    prev = nullptr;
    // if (left == right)
    //     left = nullptr;
    // if (left == this)
    //     left = nullptr;
    // if (right == this)
    //     right = nullptr;
    // if (left)
    //     delete left;
    // if (right)
    //     delete right;
    left = nullptr;
    right = nullptr;
    //word = nullptr;
}

//вставка элемента
void Trbt::Insert(TNode& new_node)
{
    TNode* prev_node = leaf;
    TNode* current_node = root;

    //идем в лист
    while (current_node != leaf) {
        prev_node = current_node;
        if (0 > strcmp(new_node.word, current_node->word)) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    //присваиваем значение узлу
    new_node.prev = prev_node;
    if (prev_node == leaf) {
        root = &new_node;
    } else if (0 > strcmp(new_node.word, prev_node->word)) {
        prev_node->left = &new_node;
    } else {
        prev_node->right = &new_node;
    }

    new_node.right = leaf;
    new_node.left = leaf;
    new_node.clr = RED;

    Fix(&new_node); //запускаем балансировку дерева
}

//левый поворот
void Trbt::LeftRotate(TNode& current_node)
{
    TNode* y = current_node.right; //берем правого сына текущего узла
    current_node.right = y->left; //записываем в него значение его левого сына

    if (y->left != leaf) { //если он не является листом, то записываем его как сына текущего узла
        y->left->prev = &current_node;
    }

    y->prev = current_node.prev; //меняем указатель на предыдущий элемент для правого сына текущего узла на предыдущий для текущего

    if (current_node.prev == leaf) { //если предыдущий для текущего - лист узла, в котором мы находимся
        root = y; //то присвоим ему правый элемент текущего узла
    } else if (&current_node == current_node.prev->left) { //если текущий узел - левый сын своего отца
        current_node.prev->left = y; //то присвоим ему правый элемент текущего узла
    } else {
        current_node.prev->right = y; //в противном случае поступим аналогично предыдущему варианту
    }

    y->left = &current_node; //присвоим полученный текущий узел в левого сына правого сына текущего узла
    current_node.prev = y; //предыдущим будет он сам
}

//правый поворот (аналогично левому)
void Trbt::RightRotate(TNode& current_node)
{
    TNode* y = current_node.left;
    current_node.left = y->right;

    if (y->right != leaf) {
        y->right->prev = &current_node;
    }

    y->prev = current_node.prev;

    if (current_node.prev == leaf) {
        root = y;
    } else if (&current_node == current_node.prev->right) {
        current_node.prev->right = y;
    } else {
        current_node.prev->left = y;
    }

    y->right = &current_node;
    current_node.prev = y;
}

//балансировка дерева при вставке
void Trbt::Fix(TNode* current_node)
{
    while (current_node->prev->clr == RED) { //пока отец красный
        if (current_node->prev == current_node->prev->prev->left) { //если отец - левый сын своего отца
            TNode* y = current_node->prev->prev->right; //смотрим дядю

            if (y->clr == RED) { //если дядя красный
                current_node->prev->clr = BLACK; //красим отца и дядю в черный
                y->clr = BLACK; //
                current_node->prev->prev->clr = RED; //красим дедушку в красный
                current_node = current_node->prev->prev; //перемещаем указатель на дедушку
            } else { //если дядя черный
                if (current_node == current_node->prev->right) {
                    current_node = current_node->prev; //если текущий узел - правый сын
                    LeftRotate(*current_node); //выполняем левый поворот текущего узла и отца
                } //указатель перемещен в бывшего отца
                current_node->prev->clr = BLACK; //красим отца в черный
                current_node->prev->prev->clr = RED; //а деда в красный
                RightRotate(*(current_node->prev->prev)); //выполняем правый поворот отца и деда
            }
        } else { //аналогично для случая, когда отец - правй сын деда
            TNode* y = current_node->prev->prev->left;

            if (y->clr == RED) {
                current_node->prev->clr = BLACK;
                y->clr = BLACK;
                current_node->prev->prev->clr = RED;
                current_node = current_node->prev->prev;
            } else {
                if (current_node == current_node->prev->left) {
                    current_node = current_node->prev;
                    RightRotate(*current_node);
                }
                current_node->prev->clr = BLACK;
                current_node->prev->prev->clr = RED;
                LeftRotate(*(current_node->prev->prev));
            }
        }
    }
    root->clr = BLACK; //красим корень в черный, чтобы свойства красно-черных деревьев не нарушались
}

//поиск по дереву
TNode* Trbt::Search(const char* pattern)
{
    TNode* tmp = root;

    while (tmp != leaf) {
        if (!strcmp(tmp->word, pattern)) {
            return tmp;
        } else if (0 > strcmp(tmp->word, pattern)) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }
    return nullptr;
}

//поиск минимума (идем в самый левый лист)
TNode* Trbt::FindMin(TNode* current_node)
{
    while (current_node->left != leaf) {
        current_node = current_node->left;
    }
    return current_node;
}

//изменение узла (нужно для удаления)
void Trbt::Exchange(TNode* old, TNode* upd)
{
    if (old->prev == leaf) {
        root = upd;
    } else if (old == old->prev->left) {
        old->prev->left = upd;
    } else {
        old->prev->right = upd;
    }
    upd->prev = old->prev;
}

//удаление узла
void Trbt::RBDelete(TNode* current_node)
{
    TNode* del_node = current_node;
    TNode* del_child = nullptr;
    color orig_clr = del_node->clr;

    if (current_node->left == leaf) { //если левый ребенок текущего узла является листом
        del_child = current_node->right; //берем правого ребенка и меняем его с текущим узлом

        Exchange(current_node, current_node->right);
    } else if (current_node->right == leaf) { //аналогично для левого ребенка
        del_child = current_node->left;

        Exchange(current_node, current_node->left);
    } else { //если же ни один ребенок не является листом
        del_node = FindMin(current_node->right);
        orig_clr = del_node->clr;
        del_child = del_node->right;

        if (del_node->prev == current_node) {
            del_child->prev = del_node;
        } else {
            Exchange(del_node, del_node->right);

            del_node->right = current_node->right;
            del_node->right->prev = del_node;
        }

        Exchange(current_node, del_node);

        del_node->left = current_node->left;
        del_node->left->prev = del_node;
        del_node->clr = current_node->clr;
    }
    if (orig_clr == BLACK) {
        FixD(del_child);
    }
    delete current_node;
}

//балансировка дерева при удалении
void Trbt::FixD(TNode* current_node)
{
    while (current_node != root && current_node->clr == BLACK) {
        if (current_node == current_node->prev->left) {
            TNode* sibling_node = current_node->prev->right;

            if (sibling_node->clr == RED) {
                sibling_node->clr = BLACK;
                current_node->prev->clr = RED;

                LeftRotate(*(current_node->prev));

                sibling_node = current_node->prev->right;
            }
            if (sibling_node->left->clr == BLACK && sibling_node->right->clr == BLACK) {
                sibling_node->clr = RED;
                current_node = current_node->prev;
            } else {
                if (sibling_node->right->clr == BLACK) {
                    sibling_node->left->clr = BLACK;
                    sibling_node->clr = RED;

                    RightRotate(*sibling_node);

                    sibling_node = current_node->prev->right;
                }
                sibling_node->clr = current_node->prev->clr;
                current_node->prev->clr = BLACK;
                sibling_node->right->clr = BLACK;

                LeftRotate(*(current_node->prev));

                current_node = root;
            }
        } else {
            TNode* sibling_node = current_node->prev->left;

            if (sibling_node->clr == RED) {
                sibling_node->clr = BLACK;
                current_node->prev->clr = RED;
                RightRotate(*(current_node->prev));
                sibling_node = current_node->prev->left;
            }
            if (sibling_node->right->clr == BLACK && sibling_node->left->clr == BLACK) {
                sibling_node->clr = RED;
                current_node = current_node->prev;
            } else {
                if (sibling_node->left->clr == BLACK) {
                    sibling_node->right->clr = BLACK;
                    sibling_node->clr = RED;

                    LeftRotate(*sibling_node);

                    sibling_node = current_node->prev->left;
                }
                sibling_node->clr = current_node->prev->clr;
                current_node->prev->clr = BLACK;
                sibling_node->left->clr = BLACK;

                RightRotate(*(current_node->prev));

                current_node = root;
            }
        }
    }
    current_node->clr = BLACK;
}

std::istream& operator>>(std::istream& is, color& clr)
{
    int tmp;
    is >> tmp;
    clr = (color)tmp;
    return is;
}

//Запись в файл от пути (проверка на возможность записи)
void Trbt::Save(const char* buffer)
{
    std::ofstream output(buffer);

    if (output.is_open()) {
        Save(output, root);
        std::cout << "OK\n";
    } else {
        std::cout << "ERROR: Couldn't create file\n";
    }

    output.close();
}

//запись в заданный файл имеющегося дерева
void Trbt::Save(std::ofstream& output, TNode* root)
{
    if (root == leaf) {
        output << LEAF << " ";
        return;
    }

    output << root->word << " " << root->key << " " << root->clr << " ";

    Save(output, root->left);
    Save(output, root->right);
}

//загрузка словаря из файла (проверка на возможность загрузки)
void Trbt::Load(const char* buffer)
{
    std::ifstream input(buffer);

    if (input.is_open()) {
        Reborn();
        Load(input, root);
        std::cout << "OK\n";
    } else {
        std::cout << "ERROR: Couldn't load file\n";
    }

    root->prev = leaf;
    input.close();
}

//загрузка словаря из данного файла
void Trbt::Load(std::ifstream& input, TNode*& root)
{
    // delete root;
    char buffer[256];
    ull key = 0;
    color clr = RED;

    if (input.peek() == EOF || (input >> buffer && !strcmp(buffer, "-1"))) {
        return;
    }

    input >> key >> clr;
    char* tmpKey = new char[strlen(buffer) + 1];
    strcpy(tmpKey, buffer);

    root = new TNode(clr, key, tmpKey);
    root->left = leaf;
    root->right = leaf;

    Load(input, root->left);
    Load(input, root->right);

    root->left->prev = root;
    root->right->prev = root;
}

//переинициализация
void Trbt::Reborn()
{
    root = leaf;
    leaf->prev = nullptr;
    leaf->left = nullptr;
    leaf->right = nullptr;
    leaf->key = 0;
    leaf->clr = BLACK;
    if (leaf->word)
        delete[] leaf->word;
    leaf->word = nullptr;
}
