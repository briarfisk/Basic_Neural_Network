#define OLC_PGE_APPLICATION
//#define OLC_PGEX_NT3

#include "olcPixelGameEngine.h"
#include "NT3_Master.h"

class Example : public olc::PixelGameEngine
{
public:

	int Current_Menu_Method;
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
		Conman.init(this);
		Current_Menu_Method = 1; //Root menu
		return true;
	}


	bool OnUserUpdate(float fElapsedTime) override
	{

		// Handle User Input
		if (GetKey(olc::Key::A).bHeld) { Conman.X_Offset_Less(1); this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this); }
		if (GetKey(olc::Key::D).bHeld) { Conman.X_Offset_More(1); this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this); }
		if (GetKey(olc::Key::W).bHeld) { Conman.Y_Offset_Less(1); this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this); }
		if (GetKey(olc::Key::S).bHeld) { Conman.Y_Offset_More(1); this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this); }


		if (GetKey(olc::Key::LEFT).bHeld) { Conman.X_Padd_Less(1); this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this); }
		if (GetKey(olc::Key::RIGHT).bHeld) { Conman.X_Padd_More(1); this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this); }
		if (GetKey(olc::Key::UP).bHeld) { Conman.Y_Padd_More(1); this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this); }
		if (GetKey(olc::Key::DOWN).bHeld) { Conman.Y_Padd_Less(1); this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this); }


		if (GetKey(olc::Key::SPACE).bPressed) { Current_Menu_Method = 0; }


		int Step_Speed = 5;
		//Root menu
		if (Current_Menu_Method == 0)
		{
			std::cout << "\n 0: Main_Menu";
			std::cout << "\n 1: Build_Mode";
			std::cout << "\n 2: Run_Sim_Free";
			std::cout << "\n 3: IDK";
			Input == "";
			std::cin >> Input;
			if (Input == "0"){ Current_Menu_Method = 0; }
			if (Input == "1"){ Current_Menu_Method = 1; }
			if (Input == "2"){ Current_Menu_Method = 2; }
			if (Input == "3"){ Current_Menu_Method = 3; }
		}
		if (Current_Menu_Method == 1)
		{
			if (Conman.is_CAN_Idle())
			{
				this->Clear(olc::BLACK); Conman.output_Nodes_GUI(this);
				std::string tmp_Input = "";
				Input = "";
				std::cout << "\n\n ->";
				//getline(std::cin, Input);
				std::cin >> tmp_Input; Input = tmp_Input; tmp_Input = "";
				for (int cou_Index = 1; cou_Index < 1; cou_Index++)
				{
					std::cin >> tmp_Input; Input += " " + tmp_Input; tmp_Input = "";
				}
				if (Input == "-exit") { Current_Menu_Method = 2; return true; }

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
				for (int cou_Step = 0; cou_Step < Step_Speed; cou_Step++)
				{
					Conman.Build_Step();
				}
			}
		}

		

		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(1900, 1000, 1, 1))
		demo.Start();

	return 0;
}