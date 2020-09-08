#include <iostream>
#include "forward_list.h"
#include "double_linked_list.h"

int main(int argc, char* argv[])
{
	{
		using namespace nmspc;

		try {

			double_linked_list<int> list;
			list.push_back(-88);
			list.pop_back();
			list.push_back(1000);
			list.push_back(-111);
	

			list.erase(0);

			for (size_t i = 0; i < list.size(); i++) 
				std::cout << list[i] << std::endl;
		}
		catch (forward_list<int>::ListException error) {

			std::cerr <<"Error:" << error.GetError() << std::endl;

		}

	}

	system("pause");

}


