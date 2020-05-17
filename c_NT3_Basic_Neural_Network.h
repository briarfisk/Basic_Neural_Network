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
        - Node_ID * Scaffold[Number_Of_Tiers][Number_Of_Nodes_On_Each_Tier]



        -- == Functions:

    //Fills out the entire CAN, using preexisting nodes where possible  
    and creating new ones when needed.
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

        -- == Contains:

    -Nodes arranged in tiers



        -- == Functions:

    //Takes a unit of input data and returns the node that is associated 
    with the unit of data.If no node currently exists for that unit of
        data then a new node is createdand associated with the unit of
        data.
        Node_ID Get_State_Node(Given_State)

        //The same as Get_State_Node(), however, no node is created if the 
        unit of data is not found.
        Node_ID Get_State_Node_For_Query(Given_State)

        //Create a connection from p_From node to p_To node for the given 
        dendrite.
        void Create_Connection(Node_ID p_From, Node_ID p_To, string
            p_Dendrite)

        //When the CAN is building it needs to know if there is a node on a 
        higher tier linking two lower tier nodes together.This function
        searches for the linking node, if no node exists then one is
        created.
        Node_ID get_Upper_Tier_Connection(Node_ID left_Node, Node_ID
            right_Node)

        //When the CAN is building for a query this function searches for then returns the upper tier linking node, however, if one does not exist then false is returned instead of a node.
        Node_ID Does_Upper_Tier_Connection_Exist(Node_ID left_Node, Node_ID
            right_Node)

        //The pattern represented by the node is backpropagated into an 
        output suitable to hold it.This is done by using an algorithm to
        trace the lower legs in the correct order to retrieve the
        information originally used in the construction of the tree that the
        current node is at the top of.
        Node_ID Get_Node_Output_Pattern(Node_ID p_Node)


        The backpropagation is initiated at the topmost treetop node.During
        backpropagation the left dendrite is done slightly different than
        the right one.The left sends a signal down both of its dendrites;
    whereas the right one only sends a signal down its right dendrite.
        This creates a wave effect when plotted that outputs the pattern
        used to construct the tree exactly as it was input.This is why
        keeping dendrite order is so important; if we did not track dendrite
        order the output would be a meaningless mess.
        void Backpropagate(Node_ID p_Node)

        //Backpropagate a left dendrite linked node.
        void Backpropagate_Left(Node_ID p_Node)

        //Backpropagate_Right a right dendrite linked node.
        void Backpropagate_Right(Node_ID p_Node)

};



        //====----------
        //==--      Node
        //====----------

class c_Node
{

        -- == Contains:

    -Current Charge
        - Base Charge

        //The action potential threshold and modifier charge function as a 
        filter when evaluating a network.Without these values then every
        single node that gets a charge will pass that charge all the way to
        the top of the network.If you have a deep network with few inputs
        you can charge the entire network at once which is usually not
        desirable.
        - Action Potential Threshold(APT)
        - Modifier Charge

        - Reinforcement Counter(RC)
        - Axons linking to the dendrites of higher nodes.

        //Node that state nodes do not have two dendrites; rather they link 
        to a single node or contain a unit of data.
        - Left Dendrite linking to a lower node.
        - Right Dendrite linking to a lower node.

        //Normal nodes do not have a state, unless you store the entire 
        pattern represented by each node with that node to allow for
        skipping the backpropagation saving on calculations.
        - Data_Unit State



        -- == Functions:

    //Adds to the nodes current charge, if the charge is over the action 
    potential threshold then it fires and sends a charge to all of the
        nodes its axons connect to in the higher tiers.
        void Charge(float p_Charge)

        //Adds to the nodes current charge, the Modifier charges role is 
        to act as a filter of sorts.When using the RC charging you modify
        the input charge based upon the RC score.
        void Add_To_Charge(float p_Charge)

        //Checks if the right dendrite value matches the given 
        p_Right_Dendrite
        bool Does_Right_Dendrite_Match(Node_ID p_Right_Dendrite)


};


#endif // !c_NT3_BASIC_NEURAL_NETWORK
