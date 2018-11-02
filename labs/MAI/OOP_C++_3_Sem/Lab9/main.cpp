#include "ntree.h"
#include "ntree_2.h"
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "=============================================" << endl;
	cout << "w for tutorial play" << endl;
	cout << "5 for inserting pent" << endl;
	cout << "6 for inserting hex" << endl;
	cout << "8 for inserting oct" << endl;
	cout << "t for inserting in global tree" << endl;
	cout << "d for delete shape" << endl;
	cout << "l for iterating local tree" << endl;
	cout << "s for size of tree" << endl;
	cout << "i for iterating" << endl;
	cout << "h for Hoar sort" << endl;
	cout << "j for parallel sort" << endl;
	cout << "p for print by path" << endl;
	cout << "q for quit" << endl;
	cout << "=============================================" << endl << endl;
	char cmd = 0;
	char path[30] = { '\0' };
	char who[2] = { '\0' };
	double length = 0.0;
	shared_ptr<TNTree<TShape>> tree(new TNTree<TShape>());
	shared_ptr<NTree_2<TNTree<TShape>>> globaltree(new NTree_2<TNTree<TShape>>());
	while (true) {
		memset(path, '\0', sizeof(char));
		cout << "cmd: ";
		cin >> cmd;
		switch (cmd) {
		case 'w': {
			typedef function<void(void)> command;
			NTree_2<command> tree_cmd;

			command cmd_insert_5 = [&]() {
				default_random_engine generator;
				uniform_int_distribution<int> dist(1, 100);

				for (int i = 0; i < 10; i++) {
					int side = dist(generator);
					tree->Insert((shared_ptr<TShape>)new TPentagon(side), "r\0", "s\0");
				}
			};
			command cmd_insert_6 = [&]() {
				default_random_engine generator;
				uniform_int_distribution<int> dist(1, 100);

				for (int i = 0; i < 10; i++) {
					int side = dist(generator);
					tree->Insert((shared_ptr<TShape>)new THexagon(side), "r\0", "s\0");
				}
			};
			command cmd_insert_8 = [&]() {
				default_random_engine generator;
				uniform_int_distribution<int> dist(1, 100);

				for (int i = 0; i < 10; i++) {
					int side = dist(generator);
					tree->Insert((shared_ptr<TShape>)new TOctagon(side), "r\0", "s\0");
				}
			};
			command cmd_print = [&]() {
				TIterator<TNode<TShape>, TShape> it_loc = tree->begin();
				TIterator<TNode<TShape>, TShape> end_loc = tree->end();
				for (it_loc, end_loc; it_loc != end_loc; it_loc++) {
					(*it_loc)->Print();
				}
				(*it_loc)->Print();
			};
			command cmd_size = [&]() {
				cout << tree->Size() << endl;
			};
			command cmd_sort = [&]() {
				tree->sort();
			};
			command cmd_parallel_sort = [&]() {
				tree->parallel_sort();
			};
			tree_cmd.Insert_2(shared_ptr<command>(&cmd_print, [](command *) {}), "r\0", "r\0");
			tree_cmd.Insert_2(shared_ptr<command>(&cmd_insert_5, [](command *) {}), "r\0", "s\0");
			tree_cmd.Insert_2(shared_ptr<command>(&cmd_insert_6, [](command *) {}), "rs\0", "s\0");
			tree_cmd.Insert_2(shared_ptr<command>(&cmd_insert_8, [](command *) {}), "rss\0", "s\0");
			tree_cmd.Insert_2(shared_ptr<command>(&cmd_size, [](command *) {}), "rs\0", "b\0");
			//tree_cmd.Insert_2(shared_ptr<command>(&cmd_sort, [](command *) {}), "rsb\0", "b\0");
			//tree_cmd.Insert_2(shared_ptr<command>(&cmd_parallel_sort, [](command *) {}), "rsbb\0", "b\0");

			TIterator<TNode_2<command>, command> it_loc = tree_cmd.begin();
			TIterator<TNode_2<command>, command> end_loc = tree_cmd.end();
			for (it_loc, end_loc; it_loc != end_loc; it_loc++) {
				shared_ptr<command> cmd = (*it_loc);
				future<void> ft = async(*cmd);
				ft.get();
				thread(*cmd).detach();
			}
			shared_ptr<command> cmd = (*it_loc);
			future<void> ft = async(*cmd);
			ft.get();
			thread(*cmd).detach();
			break;
		}
		case '5': {
			cout << "LENGTH OF PENTAGON'S EDGE: ";
			cin >> length;
			shared_ptr<TShape> shape(new TPentagon(length));
			cout << "DIRECTORY: ";
			cin >> path;
			path[29] = '\0';
			cout << "WHO: ";
			cin >> who;
			tree->Insert(shape, path, who);
			cout << "OK" << endl;
			break;
		}
		case '6': {
			cout << "LENGTH OF HEXAGON'S EDGE: ";
			cin >> length;
			shared_ptr<TShape> shape(new THexagon(length));
			cout << "DIRECTORY: ";
			cin >> path;
			path[29] = '\0';
			cout << "WHO: ";
			cin >> who;
			tree->Insert(shape, path, who);
			cout << "OK" << endl;
			break;
		}
		case '8': {
			cout << "LENGTH OCTAGON'S EDGE: ";
			cin >> length;
			shared_ptr<TShape> shape(new TOctagon(length));
			cout << "DIRECTORY: ";
			cin >> path;
			path[29] = '\0';
			cout << "WHO: ";
			cin >> who;
			tree->Insert(shape, path, who);
			cout << "OK" << endl;
			break;
		}
		case 'h': {
			cout << "SORTING" << endl;
			tree->sort();
			cout << "DONE" << endl;
			break;
		}
		case 'j': {
			cout << "PARALLEL SORTING" << endl;
			tree->parallel_sort();
			cout << "DONE" << endl;
			break;
		}
		case 't': {
			cout << "DIRECTORY: ";
			cin >> path;
			path[29] = '\0';
			cout << "WHO: ";
			cin >> who;
			globaltree->Insert_2(tree, path, who);
			shared_ptr<TNTree<TShape>> newtree(new TNTree<TShape>());
			tree = newtree;
			cout << "OK" << endl;
			break;
		}
		case 'd': {
			cout << "DIRECTORY: ";
			cin >> path;
			path[29] = '\0';
			tree->Delete(path);
			cout << "OK" << endl;
			break;
		}
		case 'p': {
			cout << "DIRECTORY: ";
			cin >> path;
			path[29] = '\0';
			tree->Print(path);
			break;
		}
		case 'l': {
			TIterator<TNode<TShape>, TShape> it_loc = tree->begin();
			TIterator<TNode<TShape>, TShape> end_loc = tree->end();
			for (it_loc, end_loc; it_loc != end_loc; it_loc++) {
				(*it_loc)->Print();
			}
			(*it_loc)->Print();
			break;
		}
		case 's': {
			cout << "QUANTITY OF TREE'S NODES: " << tree->Size() << endl;
			break;
		}
		case 'i': {
		TIterator<TNode_2<TNTree<TShape>>, TNTree<TShape>> it = globaltree->begin();
		TIterator<TNode_2<TNTree<TShape>>, TNTree<TShape>> end = globaltree->end();
		for (it, end; it != end; it++) {
			TIterator<TNode<TShape>, TShape> it_in = it->begin();
			TIterator<TNode<TShape>, TShape> end_in = it->end();
			for (it_in, end_in; it_in != end_in; it_in++) {
				(*it_in)->Print();
			}
			(*it_in)->Print();
		}
		break;
		}
		case 'q': {
			return 0;
			break;
		}
		}
	}
}