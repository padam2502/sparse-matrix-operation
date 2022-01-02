#include<iostream>
using namespace std;
struct node{
	int r;
	int c;
    double data;
	node* next;
	node(int n ,int x,double y,node* r =NULL):r(n),c(x),data(y),next(r)  {}

    };
class linked_list
{
private:
    node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(int row,int col,double new_data)
    {
        node *tmp = new node(row,col,new_data);
        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    void print()
    {
        node *tmp;
        tmp = head;
        while (tmp != NULL)
        {
            cout << tmp->r<<" "<<tmp->c<<" "<<tmp->data << endl;
            tmp = tmp->next;
        }
    }
    void MergeSort(node** headRef)
	{
    node* head = *headRef;
    node* a;
    node* b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    divide(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);
    *headRef = Merge(a, b);
	}

	node* Merge(node* a, node* b)
	{
    node* result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if ( (a->r < b->r) || ((a->r==b->r) && (a->c < b->c)) ) {
        result = a;
        result->next=Merge(a->next, b);
    }
   
    else {
        result=b;
        result->next=Merge(a, b->next);
    }
    return (result);
	}
	void divide(node* source,node** frontRef, node** backRef)
	{
    node* fast;
    node* slow;
    slow = source;
    fast = source->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
	}

    linked_list transpose()
    {
    	linked_list op;
    	node *tmp;
        tmp = head;
        while (tmp != NULL)
        {
            op.add_node(tmp->c,tmp->r,tmp->data);
            tmp = tmp->next;
        }
        MergeSort(&op.head);
        return op;
    }
    linked_list addition(linked_list s)
    {
    	linked_list op;
    	node *tmp1,*tmp2;
        tmp1=head;
        tmp2=s.head;
        while(tmp1!=NULL && tmp2!=NULL)
        {
        	if(tmp1->r==tmp2->r)
			{
				if(tmp1->c==tmp2->c)
				{
					op.add_node(tmp1->r,tmp1->c,tmp1->data+tmp2->data);
					tmp1=tmp1->next;
					tmp2=tmp2->next;
				}
				else if(tmp1->c<tmp2->c)
				{
					op.add_node(tmp1->r,tmp1->c,tmp1->data);
					tmp1=tmp1->next;
				}
				else
				{

					op.add_node(tmp2->r,tmp2->c,tmp2->data);
					tmp2=tmp2->next;
				}
				
			}
			else if(tmp1->r<tmp2->r)
				{
					op.add_node(tmp1->r,tmp1->c,tmp1->data);
					tmp1=tmp1->next;
				}
			else
			{
				op.add_node(tmp2->r,tmp2->c,tmp2->data);
					tmp2=tmp2->next;
			}
		}
		while(tmp1!=NULL)
		{
				op.add_node(tmp1->r,tmp1->c,tmp1->data);
					tmp1=tmp1->next;
		}
		while(tmp2!=NULL)
		{
				op.add_node(tmp2->r,tmp2->c,tmp2->data);
					tmp2=tmp2->next;
		}
		return op;

    }
    linked_list multiplication(linked_list s)
    {
    	linked_list res;
    	linked_list ans;
    	s=s.transpose();
    	node *tmp1,*tmp2;
        tmp1=head;
        
        double sum=0;
    	while(tmp1!=NULL)
			{
			    tmp2=s.head;
				while(tmp2!=NULL)
				{
					if(tmp1->c==tmp2->c)
					{
					    
						sum=(tmp1->data)*(tmp2->data);
						res.add_node(tmp1->r,tmp2->r,sum);
					}
					tmp2=tmp2->next;
				}
				tmp1=tmp1->next;
			}
			tmp1=res.head;
         
			while(tmp1!=NULL)
			{
			    	tmp2=tmp1->next;
				while(tmp2!=NULL)
				{
					if(tmp1->c==tmp2->c && tmp1->r==tmp2->r && tmp1->r!=-1 && tmp2->r!=-1)
					{
					    
						tmp1->data=(tmp1->data)+(tmp2->data);
						tmp2->r=-1;
						tmp2->c=-1;
						tmp2->data=-1;
						
					}
					tmp2=tmp2->next;
					
				}
				if(tmp1->r!=-1)
				ans.add_node(tmp1->r,tmp1->c,tmp1->data);
				tmp1=tmp1->next;
			}
			MergeSort(&ans.head);
			return ans;

    }
};



	int main()
	{
		int x,y,n,m;
		double v;
		linked_list a;
		cout<<"Enter matrix 1 in sparse form \n";
		cout<<"Enter number of elements in sparse matrix\n";
		cin>>n;
		cout<<"Enter row column and data value\n";

		for(int i=0;i<n;i++)
		{
			cin>>x>>y>>v;
			a.add_node(x,y,v);
		}
		cout<<"\nFirst matrix is \n";
    	a.print();
		cout<<"Enter the operantion to be performed \n";
    	cout<<" 1 for Transpose\n 2 for Multiplication\n 3 for Addition\n  ";
	    char ch;
	    cin>>ch;
    	
    	if(ch=='1')
    	{
    		
    	cout<<"\nTranspose is\n";
    	a=a.transpose();
		a.print();
    	}
    	else
    	{
    		linked_list b;
		cout<<"Enter matrix 2 in sparse form \n";
		cout<<"Enter number of elements in sparse matrix\n";
		cin>>n;
		cout<<"Enter row column and data value\n";

		for(int i=0;i<n;i++)
		{
			cin>>x>>y>>v;
			b.add_node(x,y,v);
		}
		if(ch=='3')
		{
		    cout<<"\nSecond matrix is \n";
    	b.print();
    	cout<<"\nResult is\n";
    		linked_list final=a.addition(b);
    		final.print();
    	}
    	else if(ch=='2')
    	{
    	     cout<<"\nSecond matrix is \n";
    	b.print();
    	cout<<"\nResult is\n";
    		linked_list final=a.multiplication(b);
    		final.print();
    	}
    	}

		return 0;
	}