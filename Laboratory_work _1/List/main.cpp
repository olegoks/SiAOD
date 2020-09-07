#include <iostream>
#include "ListType.h"


int main(int argc, char* argv[])
{
	{
		using namespace nmspc;

		try {

			forward_list<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(2);
			list.push_back(2);
			list.push_back(2);
		
			for (size_t i = 0; i < list.size(); i++) std::cout << list[i] << std::endl;
			
		}
		catch (forward_list<int>::ListException error) {

			std::cerr <<"Error:" << error.GetError() << std::endl;

		}

	}

	system("pause");

}


