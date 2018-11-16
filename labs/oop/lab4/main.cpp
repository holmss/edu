#include <cstdlib>
#include <iostream>

#include "pentagon.hpp"
#include "btree.hpp"
#include "figure.hpp"

int main()
{
    TTree<Figure> node;
    char inp;
    char path[10];
   // Pentagon * pent;
    
    std::cout << "Enter 'h' for help" << std::endl;
    while (std::cin.get(inp))
    {
        if (inp == '\n')
            continue;
        if (inp == '+')
        {
            node.add(std::shared_ptr<Figure>(new Pentagon(std::cin)));
        }
        else if (inp == '-')
        {
            std::cin >> path;
            node.Remove(node.get(path));
        }
	else if (inp == 's')
	{
	    std::cin >> path;
	    std::cout << "square = " << node.getItem(path)->Square() << std::endl;
	} 
	else if (inp == 'h') 
	{
	    std::cout << "Add element: + \nRemove element: -" << std::endl;
	}
        std::cout << node;
	std::cout << "-------------------------------------------------" << std::endl;
    }

    return 0;
}
