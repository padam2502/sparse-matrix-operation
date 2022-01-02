#include<iostream>
using namespace std;
class matrix{
	const static int size = 100005;
public:
	int row;
	int column;
	int count;
	double **mat;
	matrix(int r,int c)
	{
		row=r;
		column=c;
		count=0;
		mat=new double*[size];
		for (int i=0; i<size; i++)
            mat[i] = new double[3];
	}
	void print()
	{
		for(int i=0;i<count;i++)
		{
			cout<<mat[i][0]<<" "<<mat[i][1]<<" "<<mat[i][2]<<endl;
		}
	}
	matrix transpose()
	{
		matrix op(column,row);
		op.count=count;
		int temp[column]={0};
		int cumulative[column+1]={0};
		for(int i=0;i<count;i++)
            temp[(int)mat[i][1]]++;
        for(int i=1;i<=column; i++)
            cumulative[i]=temp[i-1]+cumulative[i-1];
        for(int i=0;i<count;i++)
        {
        	int p=cumulative[(int)mat[i][1]];
        	++cumulative[(int)mat[i][1]];
        	op.mat[p][0]=mat[i][1];
        	op.mat[p][1]=mat[i][0];
        	op.mat[p][2]=mat[i][2];
        }

        return op;

	}
	matrix add(matrix s)
	{
		 if (row != s.row || column != s.column)
        {
           cout<<"Addition not possible\n";
        }
		matrix ans(row,column);
		int p=0;
		int q=0;
		int t=0;
		while(p<count && q<s.count)
		{
			if(mat[p][0]==s.mat[q][0])
			{
				if(mat[p][1]==s.mat[q][1])
				{
					ans.mat[t][0]=mat[p][0];
					ans.mat[t][1]=mat[p][1];
					ans.mat[t++][2]=mat[p][2]+s.mat[q][2];
					++p;++q;
				}
				else if(mat[p][1]<s.mat[q][1])
				{

					ans.mat[t][0]=mat[p][0];
					ans.mat[t][1]=mat[p][1];
					ans.mat[t++][2]=mat[p][2];
					++p;
				}
				else
				{

					ans.mat[t][0]=s.mat[q][0];
					ans.mat[t][1]=s.mat[q][1];
					ans.mat[t++][2]=s.mat[q][2];
					++q;
				}
				
			}
			else if(mat[p][0]<s.mat[q][0])
			{
				ans.mat[t][0]=mat[p][0];
					ans.mat[t][1]=mat[p][1];
					ans.mat[t++][2]=mat[p][2];
					++p;
			}
			else
			{
				ans.mat[t][0]=s.mat[q][0];
					ans.mat[t][1]=s.mat[q][1];
					ans.mat[t++][2]=s.mat[q][2];
					++q;
			}
		}
		while(p<count)
		{
				ans.mat[t][0]=mat[p][0];
					ans.mat[t][1]=mat[p][1];
					ans.mat[t++][2]=mat[p][2];
					++p;
		}
		while(q<s.count)
		{
			ans.mat[t][0]=s.mat[q][0];
					ans.mat[t][1]=s.mat[q][1];
					ans.mat[t++][2]=s.mat[q][2];
					++q;
		}
		ans.count=t;
		cout<<"\n Addition is\n";
		return ans;
	}
	matrix mul(matrix s)
	{
		if(s.row != column)
		{
		    cout<<s.row<<" "<<column<<endl;
		    cout<<row<<" "<<s.column<<endl;
			cout<<"Multiplication not possible\n";
		}
		else
		{
			matrix res(row,s.column);
			matrix ans(row,s.column);
			s=s.transpose();
			int p=0;int q=0;
			int t=0;
			double sum=0;
			for(int i=0;i<count;i++)
			{
				for(int j=0;j<s.count;j++)
				{
					if(mat[i][1]==s.mat[j][1])
					{
					    
						sum=(mat[i][2])*(s.mat[j][2]);
						res.mat[t][0]=mat[i][0];
						res.mat[t][1]=s.mat[j][0];
						res.mat[t++][2]=sum;
					}
				}
			}
			
			res.count=t;
			for(int i=0;i<t;i++)
			{
				for(int j=i+1;j<t;j++)
				{
					if(res.mat[i][0]==res.mat[j][0] && res.mat[i][1]==res.mat[j][1] && res.mat[i][0]!=-1 && res.mat[j][0]!=-1)
					{
						res.mat[i][2]+=res.mat[j][2];
						res.mat[j][0]=-1;
						res.mat[j][1]=-1;
						res.mat[j][2]=-1;
					}
				}
			}
			int w=0;
			for(int i=0;i<t;i++)
			{
				if(res.mat[i][0]!=-1)
				{
						ans.mat[w][0]=res.mat[i][0];
						ans.mat[w][1]=res.mat[i][1];
						ans.mat[w++][2]=res.mat[i][2];
				}
			}
			
			ans.count=w;

			for(int i=0;i<w-1;i++)
			{
				for(int j=0;j<w-1-i;j++)
				{
					if(ans.mat[j][1]>ans.mat[j+1][1] && ans.mat[j][0]==ans.mat[j+1][0])
					{
						double x=ans.mat[j][1];
						ans.mat[j][1]=ans.mat[j+1][1];
						ans.mat[j+1][1]=x;
						x=ans.mat[j][2];
						ans.mat[j][2]=ans.mat[j+1][2];
						ans.mat[j+1][2]=x;
					}
				}
			}
			
			return ans;
		}
	}
	

};

int main()
{
    long long n,m,c=0;
    cout<<"Enter the first matrix\n";
    cout<<"Enter number of rows \n";
	cin>>n;
	cout<<"Enter number of columns \n";
	cin>>m;
	cout<<"Enter orignal matrix\n";
	double arr[n][m];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>arr[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(arr[i][j])++c;
		}
	}
	matrix ob(n,m);
	ob.count=c;
	int k=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(arr[i][j])
			{
				ob.mat[k][0]=i;
				ob.mat[k][1]=j;
				ob.mat[k][2]=arr[i][j];
				++k;
			}
		}
	}
    cout<<"Enter the operantion to be performed \n";
    cout<<" 1 for Transpose\n 2 for Multiplication\n 3 for Addition\n  ";
    char ch;
    cin>>ch;
    {
    if(ch=='1')
    {
    	cout<<"\nFirst matrix is \n";
    	ob.print();
    	cout<<"\nTranspose is\n";
    	ob=ob.transpose();
		ob.print();
		
    }
	
	else
	{
	    cout<<"\nFirst matrix is \n";
    	ob.print();
		cout<<"\nEnter second matrix\n";
		cout<<"\nEnter number of rows \n";
		cin>>n;
		cout<<"\nEnter number of columns \n";
		cin>>m;
		cout<<"\nEnter orignal matrix\n";
		double arr2[n][m];
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
			cin>>arr2[i][j];
			}
		}
		c=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(arr2[i][j])++c;
			}
		}
		matrix ob2(n,m);
		ob2.count=c;
		 k=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(arr2[i][j])
				{
					ob2.mat[k][0]=i;
					ob2.mat[k][1]=j;
					ob2.mat[k][2]=arr2[i][j];
					++k;
				}
			}
		}
		cout<<"\nSecond matrix is \n";
		ob2.print();
		if(ch=='2')
		{
			matrix final=ob.mul(ob2);
			cout<<"\nMultiplication is\n";
			final.print();
		}
		else if(ch=='3')
		{
			matrix final=ob.add(ob2);
			final.print();
		}
		else cout<<"\nError\n";

	}
}
	return 0;
}