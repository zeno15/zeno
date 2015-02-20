#include <InputImplementationUnix.hpp>


char keys_return[32];
	
	Display *dis = XOpenDisplay(NULL);
	
	XQueryKeymap(dis, keys_return);
	
	for (unsigned int i = 0; i < 32; i += 1)
	{
		for (unsigned int j = 0; j < 8; j += 1)
		{
			if (((keys_return[i] >> j) & 1) != 0)
			{
				/*
				 * 4.4 = ENTER
				 * 4.6 = A
				 * 6.2 = L-SHIFT
				 */
				std::cout << i << "." << j << ": " << ((keys_return[i] >> j) & 1) << std::endl;
			}
		}
	}
	XCloseDisplay(dis);

