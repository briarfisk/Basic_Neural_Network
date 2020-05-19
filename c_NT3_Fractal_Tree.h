


/*
		When I was building the networks I ran into the problem of searching them for existing state nodes. A state
	node is the node that associates an input with a node. State nodes allows for storing information in the networks and
	subsequently retrieving information from them. With the higher networks that used node IDs (NID)s from the lower
	constructs this became an issue because the number of unique nodes input into the network could get into the millions.
		In building a network you have to first take an input and search the network to see if that state was already
	associated with a node. Originally this was done with binary trees. The millions of unique inputs into these binary
	trees caused long search times. When it came to reading the nodes in there was another issue with the NIDs being
	sequential leading to extremely long branches in the binary tree that stored almost all of the nodes. This led to
	stack corruption with recusive searches.
		The first thing done was changing the recursive searches to an iterative one. This solved the issue of stack
	corruption but did nothing to solve the long search times. So then an optimization function was created which
	redistributed the nodes evenly along the branches. This function helped but did not fix the issue as the optimization
	had to be done frequently and was costly in and of itself.
		In the end I used a trinary tree combined with bit shifting the query. This allowed for a tree that has branches
	with fixed lengths. With the branches not getting excessive it does not run into the problem of stack corruptions
	even with millions of entries.
*/


//This class forms the basic node on which the fractal tree is built.
class c_NT3_Fractal_State_Node
{
	friend class c_NT3_Fractal_State_Tree;
private:

	//Legs of the node.
	c_NT3_Fractal_State_Node* Right;
	c_NT3_Fractal_State_Node* Center;
	c_NT3_Fractal_State_Node* Left;

public:

	//This stores the state. It is a union.
	u_Data_3 Data;

	//Pointer to the actual node.
	c_NT3_Base_Node_1D* NID;

	c_NT3_Fractal_State_Node()
	{
		Right = NULL;
		Center = NULL;
		Left = NULL;
		Data.I = 0;
	}

	~c_NT3_Fractal_State_Node()
	{
		if (Right != NULL) { delete Right; Right = NULL; }
		if (Center != NULL) { delete Center; Center = NULL; }
		if (Left != NULL) { delete Left; Left = NULL; }
	}

};

//The fractal state tree is a trinary tree that uses a bitshifted input to dtermine which nodes to assign.
class c_NT3_Fractal_State_Tree
{
private:


public:

	//The root node.
	c_NT3_Fractal_State_Node* Root;

	//the current node that will allow referencing outside of the search function.
	c_NT3_Fractal_State_Node** Current;

	//the flag that set when a node is found already set
	bool flg_Foundit;

	//Holds the bitshifted data to compare to the nodes data.
	u_Data_3 tmp_Data;

	c_NT3_Fractal_State_Tree()
	{
		Root = NULL;
		Current = NULL;
		flg_Foundit = false;

		tmp_Data.U = 0;
	}

	~c_NT3_Fractal_State_Tree()
	{
		if (Root != NULL) { delete Root; Root = NULL; }
	}
	
	//Resets the tree.
	void reset()
	{
		if (Root != NULL) { delete Root; Root = NULL; }
	}

	//Search for a state.
	void search(u_Data_3 p_Data)
	{
		//Set the flag to indicate that the data was not found.
		flg_Foundit = false;

		tmp_Data.U = 0;

		//The union is 64 bits deep. So start the shift at 63.
		query_Node(Root, p_Data, 63);
	}

	//Queries a node. 
	//p_Node is the node to check against the query value.
	//p_Data is the data that is checked against.
	//p_Shift is the number of bits to extract for comparison.
	int query_Node(c_NT3_Fractal_State_Node*& p_Node, u_Data_3 p_Data, int p_Shift)
	{
		//Shift the data to get the temporary value.
		tmp_Data.U = p_Data.U >> p_Shift;

		//If the passed node is NULL create it.
		if (p_Node == NULL)
		{
			p_Node = new c_NT3_Fractal_State_Node;
			p_Node->Right = NULL;
			p_Node->Center = NULL;
			p_Node->Left = NULL;
			p_Node->NID = NULL;


			if (p_Shift >= 1)
			{
				//If the query is not at the end set the data to tmp_Data rather than p_Data.
				p_Node->Data = tmp_Data;
			}
			else
			{
				//If the query has reached the end set the data to the full query data.
				p_Node->Data = p_Data;

				//Set the current node to the newly created node.
				Current = &p_Node;

				//The node was not found, one had to be created.
				flg_Foundit = false;

				//Return as we are done here.
				return 0;
			}
		}

		//If the current data matches the tmp data then another depth is explored.
		if (p_Node->Data.U == tmp_Data.U && p_Shift >= 1)
		{
			if (p_Shift == 1) { query_Node(p_Node->Center, p_Data, 0); return 0; }
			query_Node(p_Node->Center, p_Data, (p_Shift - 2));
			return 0;
		}

		//If the node data matches the given data exactly the node has been found.
		//Set Current to the current node.
		//Set the flg_Foundit to true as the node was found without creating it.
		if (p_Node->Data.U == p_Data.U)
		{
			Current = &p_Node;
			if (p_Node->NID != NULL) { flg_Foundit = true; }
			return 0;
		}

		//If the tmp_Data is less than the nodes data then look on the left leg.
		if (tmp_Data.U < p_Node->Data.U)
		{
			query_Node(p_Node->Left, p_Data, p_Shift);
			return 0;
		}

		//If the tmp_Data is more than the nodes data then look on the right leg.
		if (tmp_Data.U > p_Node->Data.U)
		{
			query_Node(p_Node->Right, p_Data, p_Shift);
			return 0;
		}
		return 0;
	}

	//Outputs the tree starting at the root node.
	void output_Tree()
	{
		output_Node(Root, 0);
	}

	//Outputs a given node. p_Tab determines an offset during output.
	void output_Node(c_NT3_Fractal_State_Node * &p_Node, int p_Tab)
	{
		if (p_Node == NULL) { return; }
		output_Node(p_Node->Left, (p_Tab));
		std::cout << "\n";
		for (int cou_Index = 0; cou_Index < p_Tab; cou_Index++)
		{
			std::cout << "  ";
		}
		std::cout << (p_Node->Data).U << "->";
		if (p_Node->NID != NULL) 
		{ std::cout << (p_Node->NID); }
		else { std::cout << "NULL"; }
		output_Node(p_Node->Center, (p_Tab + 1));
		output_Node(p_Node->Right, (p_Tab));
	}

	//Outputs the tree with the backpropagation from the nodes starting at the root node.
	void output_Tree_BP()
	{
		std::cout << "\n\t Fractal Tree Backpropagation Station";
		output_Node_BP(Root);
	}

	//Outputs a given node and backpropagates the node it is linked to.
	void output_Node_BP(c_NT3_Fractal_State_Node * &p_Node)
	{
		if (p_Node == NULL) { return; }
		output_Node_BP(p_Node->Left);
		if ((p_Node->NID) != NULL) { std::cout << "\n\t" << (p_Node->Data).I << "->" << (p_Node->NID); (p_Node->NID)->bp_O(); }
		output_Node_BP(p_Node->Center);
		output_Node_BP(p_Node->Right);
	}

	//Retrieves the NID from a given node.
	c_NT3_Base_Node_1D* get_Node_NID(c_NT3_Fractal_State_Node * &p_Node)
	{
		if (p_Node != NULL)
		{
			return p_Node->NID;
		}
		else {
			return NULL;
		}
	}

	//Sets a node NID.
	void set_Node_NID(c_NT3_Fractal_State_Node * &p_Node, c_NT3_Base_Node_1D * p_NID)
	{
		if (p_Node != NULL)
		{
			p_Node->NID = p_NID;
		}
	}

	//Sets the current nodes NID.
	c_NT3_Base_Node_1D* set_Current_Node_NID(c_NT3_Base_Node_1D * p_NID)
	{
		set_Node_NID(*Current, p_NID);
		return p_NID;
	}

	//Gets the current nodes NID.
	c_NT3_Base_Node_1D* get_Current_Node_NID()
	{
		return get_Node_NID(*Current);
	}
};
