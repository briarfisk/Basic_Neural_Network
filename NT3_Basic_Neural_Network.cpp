#define OLC_PGE_APPLICATION
//#define OLC_PGEX_NT3

#include "olcPixelGameEngine.h"
#include "NT3_Master.h"

class Example : public olc::PixelGameEngine
{
public:

	olc::NT3::c_NT3_Construct_1D Conman;
	std::string Input;

	Example()
	{
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		olc::NT3::init_LoTd();
		Conman.set_PGE(this);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (Conman.is_CAN_Idle())
		{
			std::string tmp_Input = "";
			Input = "";
			std::cout << "\n\n ->";
			//getline(std::cin, Input);
			for (int cou_Index = 0; cou_Index < 1; cou_Index++)
			{
				std::cin >> tmp_Input; Input += " " + tmp_Input; tmp_Input = "";
			}

			if (Input.size() > 1) 
			{
				Conman.reset_Inputs();
				Conman.in(0, 0, Input);
				Conman.Start_Build_Stepping();
				//Conman.output_Nodes_Raw();

				Conman.output_Nodes_Stats();

				std::cout << "\n\n Current Input string:\n__________\n";
				olc::NT3::ostr(0, 14, Input);
				std::cout << "\n__________\n";
			}

		}
		else
		{
			Conman.Build_Step();
		}
		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(1500, 1000, 1, 1))
		demo.Start();

	return 0;
}