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
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		std::cout << "\n\n ->";
		getline(std::cin, Input);
		Conman.in(0, 0, Input);
		Conman.Build();
		//Conman.output_Nodes_Raw();

		Conman.output_Nodes_Stats();

		Conman.output_Nodes_GUI(this);

		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(1000, 1000, 1, 1))
		demo.Start();

	return 0;
}