/*
    Briar Fisk
    17th May 2020
    C++ generated from:
    "NT3_Basic_Neural_Network_Pseudocode.txt"

    ---Note, although it is called, "Basic_Neural_Netowrk," the class
    -that actually encapsulates everything is called a Construct.
*/

#ifndef c_NT3_BASIC_NEURAL_NETWORK
#define c_NT3_BASIC_NEURAL_NETWORK

#include "c_NT3_Basic_Neural_Network.cpp"


//====----------
//==--      Node
//====----------

class c_Node
{
private:

    //Static settings shared among all nodes.
    static double Base_Charge;

    //Settings
    double Action_Potential_Threshold;
    double Modifier_Charge;
    bool Charging_Legs[2];

    //Node current stats.
    double Reinforcement_Counter;
    double Current_Charge;
    char State;

    //Node connections
    c_Node** Axons;
    int Axon_Count;
    c_Node* Dendrites[2];

public:

    void Charge(double p_Charge);
    void Add_To_Charge(double p_Charge);

    bool Does_Right_Dendrite_Match(c_Node* p_Right_Dendrite);
};
c_Node::Base_Charge = 1.0;



        //====----------------
        //==--      Construct
        //====----------------

class c_Construct
{

    //-Current Active Nodes(CAN)
        //- Node Network
        //- Input and Output tables

    //Eval is used to search the node network for the input pattern.
    void Eval();

    /*Build is used when training to construct a representation of the
    input data in the node network.
    */
    void Build();

    /*Takes an input into the construct so that it can be read in and
    built, or queried.The input can be a bytestring, array of integers,
    array of floats, or any set of data that can be represented by a one
    dimensional array.
    */
    void Submit_Input(std::string p_Input);

    /*Starting at a given tier (Low_Tier) the CAN is charged until the
    topmost given tier is reached.This function is called after the CAN
    has been built and uses the scaffold erected in the CAN.
    */
    void Charge(int Low_Tier, int High_Tier);

    /*For all of the charged treetop nodes after evaluation gather the
    patterns that the treetop nodes represent and store the gathered
    patterns in the output.Other information about the treetops can be
    gathered, such as the charge.
    */
    void Gather_Output();

};


        //====----------------------------------------
        //==--      Current Active Nodes (CAN)
        //====----------------------------------------

class c_Current_Active_Nodes
{
    //The CAN requires access to the node networks members that allow for 
    //-Access to the node network

        /*The CAN builds the input from the construct.
        - Access to the input of the construct
        */

        /*The node scaffold is a two dimensional array of Node_ID references. 
        It is expanded to hold the construct necessary to represent the
        input pattern.The first index represents the height of the scaffold
        in tiers which is equal to the length of the input set.The number
        of nodes on each tier decreases with each step up the scaffold by
        one to form a pyramidal structure.
        */
        //Node_ID * Scaffold[Number_Of_Tiers][Number_Of_Nodes_On_Each_Tier]



        -- == Functions:

    //Fills out the entire CAN, using preexisting nodes where possible  
    //and creating new ones when needed.
        void Build()

        //Fills out the CAN but only with preexisting nodes, it does not 
        create new ones.
        void Query()

        //Resizes the CAN scaffold based upon the size of the input.
        void Resize()

        //Gathers the state nodes associated with each unit of input.
        void Fill_State()

        //Gathers the state node associated with each unit of input, but does 
        not create them if they are not found.Used for building a query.
        void Query_State()

        //Builds the node tiers after the input has been read in as state nodes.
        void Build_Tiers_Full()

        //Builds the node tiers after the input has been read in as state 
        nodes but does not create new nodes.
        void Build_Tiers_Query()


        //Reinforces the nodes currently in the CAN scaffold.
        void Reinforce()

};

        //====----------------------
        //==--      Node Network
        //====----------------------

class c_Node_Network
{
    c_Node



        Node_ID Get_State_Node(Given_State)
        Node_ID Get_State_Node_For_Query(Given_State)
        void Create_Connection(Node_ID p_From, Node_ID p_To, string
            p_Dendrite)
        Node_ID get_Upper_Tier_Connection(Node_ID left_Node, Node_ID
            right_Node)
        Node_ID Does_Upper_Tier_Connection_Exist(Node_ID left_Node, Node_ID
            right_Node)
        Node_ID Get_Node_Output_Pattern(Node_ID p_Node)

        void Backpropagate(Node_ID p_Node)

        void Backpropagate_Left(Node_ID p_Node)

        void Backpropagate_Right(Node_ID p_Node)

};



#endif // !c_NT3_BASIC_NEURAL_NETWORK
