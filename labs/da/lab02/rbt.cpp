#include "rbt.hpp"

TRBtree::TRBtree() {
    leaf = new TNode(BLACK, 0, nullptr);
    root = leaf;
}

TRBtree::TNode::TNode(color new_clr, ull new_value, char* new_key) {
    prev = nullptr;
    left = nullptr;
    right = nullptr;
    value = new_value;
    clr = new_clr;
    key = new_key;
}

TRBtree::TNode::~TNode() {
    delete [] key;

    prev = nullptr;
    left = nullptr;
    right = nullptr;
    key = nullptr;
}

//вставка элемента
void TRBtree::Insert(TNode& new_node) {
    TNode* prev_node = this->leaf;
    TNode* current_node = this->root;

    //идем в лист
    while(current_node != this->leaf) {
        prev_node = current_node;
        if(0 > strcmp(new_node.key, current_node->key)) {
            current_node = current_node->left;
        }
        else {
            current_node = current_node->right;
        }
    }

    //присваиваем значение узлу
    new_node.prev = prev_node;
    if(prev_node == this->leaf) {
        this->root = &new_node;
    }
    else if(0 > strcmp(new_node.key, prev_node->key)) {
        prev_node->left = &new_node;
    }
    else {
        prev_node->right = &new_node;
    }

    new_node.right = this->leaf;
    new_node.left = this->leaf;
    new_node.clr = RED;
    
    Fix(&new_node); //запускаем балансировку дерева
}

//левый поворот
void TRBtree::LeftRotate(TNode& current_node) {
    TNode* y = current_node.right;                      //берем правого сына текущего узла
    current_node.right = y->left;                       //записываем в него значение его левого сына 
    
    if(y->left != this->leaf) {                         //если он не является листом, то записываем его как сына текущего узла
        y->left->prev = &current_node;
    }
    
    y->prev = current_node.prev;                        //меняем указатель на предыдущий элемент для правого сына текущего узла на предыдущий для текущего
    
    if(current_node.prev == this->leaf) {               //если предыдущий для текущего - лист узла, в котором мы находимся
        this->root = y;                             //то присвоим ему правый элемент текущего узла
    }
    else if(&current_node == current_node.prev->left) { //если текущий узел - левый сын своего отца
        current_node.prev->left = y;                //то присвоим ему правый элемент текущего узла
    }
    else {
        current_node.prev->right = y;                   //в противном случае поступим аналогично предыдущему варианту
    }
    
    y->left = &current_node;                            //присвоим полученный текущий узел в левого сына правого сына текущего узла
    current_node.prev = y;                              //предыдущим будет он сам
}

//правый поворот (аналогично левому)
void TRBtree::RightRotate(TNode& current_node) {
    TNode* y = current_node.left;
    current_node.left = y->right;

    if(y->right != this->leaf) {
        y->right->prev = &current_node;
    }
    
    y->prev = current_node.prev;
    
    if(current_node.prev == this->leaf) {
        this->root = y;
    }
    else if(&current_node == current_node.prev->right) {
        current_node.prev->right = y;
    }
    else {
        current_node.prev->left = y;
    }
    
    y->right = &current_node;
    current_node.prev = y;
}

//балансировка дерева при вставке
void TRBtree::Fix(TNode* current_node) {
    while(current_node->prev->clr == RED) {//пока отец красный
        if(current_node->prev == current_node->prev->prev->left) {  //если отец - левый сын своего отца
            TNode* y = current_node->prev->prev->right;         //смотрим дядю
    
            if(y->clr == RED) {                             //если дядя красный
                current_node->prev->clr = BLACK;        //красим отца и дядю в черный
                y->clr = BLACK;                         //
                current_node->prev->prev->clr = RED;    //красим дедушку в красный
                current_node = current_node->prev->prev;//перемещаем указатель на дедушку
            }
            else {                                          //если дядя черный
                if(current_node == current_node->prev->right) {
                    current_node = current_node->prev;  //если текущий узел - правый сын
                    LeftRotate(*current_node);          //выполняем левый поворот текущего узла и отца
                }                                       //указатель перемещен в бывшего отца
                current_node->prev->clr = BLACK;        //красим отца в черный
                current_node->prev->prev->clr = RED;    //а деда в красный
                RightRotate(*(current_node->prev->prev));//выполняем правый поворот отца и деда
            }
        } 
        else {                                                      //аналогично для случая, когда отец - правй сын деда
            TNode* y = current_node->prev->prev->left;
            
            if(y->clr == RED) {
                current_node->prev->clr = BLACK;
                y->clr = BLACK;
                current_node->prev->prev->clr = RED;
                current_node = current_node->prev->prev;
            } 
            else {
                if(current_node == current_node->prev->left) {
                    current_node = current_node->prev;
                    RightRotate(*current_node);
                }
                current_node->prev->clr = BLACK;
                current_node->prev->prev->clr = RED;
                LeftRotate(*(current_node->prev->prev));
            }
        }
    }
    this->root->clr = BLACK; //красим корень в черный, чтобы свойства красно-черных деревьев не нарушались
}

//поиск по дереву
TRBtree::TNode* TRBtree::Search(const char* pattern) {
    TNode* tmp = this->root;

    while(tmp != this->leaf) {
        if(!strcmp(tmp->key, pattern)) {
            return tmp;
        } 
        else if(0 > strcmp(tmp->key, pattern)) {
            tmp = tmp->right;
        } 
        else {
            tmp = tmp->left;
        }
    }
    return nullptr;
}

//поиск минимума (идем в самый левый лист)
TRBtree::TNode* TRBtree::FindMin(TNode* current_node) {
    while(current_node->left != this->leaf) {
        current_node = current_node->left;
    }
    return current_node;
}

//изменение узла (нужно для удаления)
void TRBtree::Exchange(TNode* old, TNode* upd) {
    if(old->prev == this->leaf) {
        this->root = upd;
    } else if(old == old->prev->left) {
        old->prev->left = upd;
    } else {
        old->prev->right = upd;
    }
    upd->prev = old->prev;
}

//удаление узла
void TRBtree::RBDelete(TNode* current_node) {
    TNode* del_node = current_node;
    TNode* del_child = nullptr;
    color orig_clr = del_node->clr;

    if(current_node->left == this->leaf) {                  //если левый ребенок текущего узла является листом
        del_child = current_node->right;                    //берем правого ребенка и меняем его с текущим узлом
    
        Exchange(current_node, current_node->right);
    } 
    else if(current_node->right == this->leaf) {            //аналогично для левого ребенка
        del_child = current_node->left;
    
        Exchange(current_node, current_node->left);
    } 
    else {                                                  //если же ни один ребенок не является листом
        del_node = FindMin(current_node->right);            
        orig_clr = del_node->clr;
        del_child = del_node->right;
    
        if(del_node->prev == current_node) {                
            del_child->prev = del_node;                     
        } 
        else {
            Exchange(del_node, del_node->right);
        
            del_node->right = current_node->right;
            del_node->right->prev = del_node;
        }
        
        Exchange(current_node, del_node);
        
        del_node->left = current_node->left;
        del_node->left->prev = del_node;
        del_node->clr = current_node->clr;
    }
    if(orig_clr == BLACK) {
        FixD(del_child);
    }
    delete current_node;
}

//балансировка дерева при удалении
void TRBtree::FixD(TNode* current_node) {
    while(current_node != this->root && current_node->clr == BLACK) {
        if(current_node == current_node->prev->left) {
            TNode* sibling_node = current_node->prev->right;
       
            if(sibling_node->clr == RED) {
                sibling_node->clr = BLACK;
                current_node->prev->clr = RED;
       
                LeftRotate(*(current_node->prev));
       
                sibling_node = current_node->prev->right;
            }
            if(sibling_node->left->clr == BLACK && sibling_node->right->clr == BLACK) {
                sibling_node->clr = RED;
                current_node = current_node->prev;
            } 
            else {
                if(sibling_node->right->clr == BLACK) {
                    sibling_node->left->clr = BLACK;
                    sibling_node->clr = RED;
            
                    RightRotate(*sibling_node);
            
                    sibling_node = current_node->prev->right;
                }
                sibling_node->clr = current_node->prev->clr;
                current_node->prev->clr = BLACK;
                sibling_node->right->clr = BLACK;
            
                LeftRotate(*(current_node->prev));
            
                current_node = this->root;
            }
        } 
        else {
            TNode* sibling_node = current_node->prev->left;
        
            if(sibling_node->clr == RED) {
                sibling_node->clr = BLACK;
                current_node->prev->clr = RED;
                RightRotate(*(current_node->prev));
                sibling_node = current_node->prev->left;
            }
            if(sibling_node->right->clr == BLACK && sibling_node->left->clr == BLACK) {
                sibling_node->clr = RED;
                current_node = current_node->prev;
            } 
            else {
                if(sibling_node->left->clr == BLACK) {
                    sibling_node->right->clr = BLACK;
                    sibling_node->clr = RED;
            
                    LeftRotate(*sibling_node);
            
                    sibling_node = current_node->prev->left;
                }
                sibling_node->clr = current_node->prev->clr;
                current_node->prev->clr = BLACK;
                sibling_node->left->clr = BLACK;
            
                RightRotate(*(current_node->prev));
            
                current_node = this->root;
            }
        }
    }
    current_node->clr = BLACK;
}

std::istream& operator>>(std::istream& is, const color& clr) {
    is >> clr;
    return is;
}

//Запись в файл от пути (проверка на возможность записи)
void TRBtree::Save(const char* buffer) {
    std::ofstream output(buffer);
    
    if(output.is_open()) {
        Save(output, this->root);
        std::cout << "OK\n";
    } 
    else {
        std::cout << "ERROR: Couldn't create file\n";
    }
    
    output.close();
}

//запись в заданный файл имеющегося дерева
void TRBtree::Save(std::ofstream& output, TNode* root) {
    if(root == this->leaf) {
        output << LEAF << " ";
        return;
    }
    
    output << root->key << " " << root-> value << " " << root->clr << " ";
    
    Save(output, root->left);
    Save(output, root->right);
}

//загрузка словаря из файла (проверка на возможность загрузки)
void TRBtree::Load(const char* buffer) {
    std::ifstream input(buffer);
    
    if(input.is_open()) {
        Reborn();
        Load(input, this->root);
        std::cout << "OK\n";
    } 
    else {
        std::cout << "ERROR: Couldn't load file\n";
    }
    
    root->prev = this->leaf;
    input.close();
}

//загрузка словаря из данного файла
void TRBtree::Load(std::ifstream& input, TNode*& root) {
    char buffer[256];
    ull value = 0;
    color clr = RED;
    
    if(input.peek() == EOF || (input >> buffer && !strcmp(buffer, "-1"))) {
        return;
    }

    input >> value >> clr;
    char* tmpKey = new char[strlen(buffer) + 1];
    strcpy(tmpKey, buffer);

    root = new TNode(clr, value, tmpKey);
    root->left = this->leaf;
    root->right = this->leaf;
    
    Load(input, root->left);
    Load(input, root->right);
    
    root->left->prev = root;
    root->right->prev = root;
}

//переинициализация
void TRBtree::Reborn() {
    this->root = this->leaf;
    this->leaf->prev = nullptr;
    this->leaf->left = nullptr;
    this->leaf->right = nullptr;
    this->leaf->value = 0;
    this->leaf->clr = BLACK;
    this->leaf->key = nullptr;
}

