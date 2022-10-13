/*
Powered by Hizitok

A non-recusive algorithm for Ackerman function

This file is running under GNU license.
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1>>10
using namespace std;

int mem[100][100];
int Ackerman_dfs(int m_, int n_)
{
	if(!m_) return n_+1;
	// Memorized search
	//if(mem[m_][n_]) return mem[m_][n_];
	//	cout << "Computing Ackerman( "<< m_ <<" , " << n_ <<" )\n";  
	int ans = n_?(Ackerman_dfs(m_-1,Ackerman_dfs(m_,n_-1))):(Ackerman_dfs(m_-1,1));
	mem[m_][n_] = ans; 
	return ans;
}

struct arr
{
	int m,n;
	int status, value;
	arr(){ m = 0, n = 0, value = 0, status = 0; }
	arr(int _M, int _N, int _S=0, int _V=0)
	{
		m = _M, n = _N, status = _S, value = _V;
	}
	//status: 0: uncomputed; 1: waiting value; 2: value completed
};
int mem2[100][100];
int Ackerman_norm(int m_,int n_)
{
	int ans,head;
	arr stk[100];
	arr *p;
	
	head = 1;
	stk[head] = arr(m_,n_);
	while(head > 0)
	{
		p = &stk[head];
		
		if( !(p->m) ) 
		{
			p->value = p->n +1;
			p->status = 2;
			head--;	continue;
		}
		if( !(p->n) )
		{
			p->m = p->m-1;
			p->n = 1;
			continue;
		}
		if( p->m && p->n )
		{
			if( p->status == 0 )
			{
				// Memorized search
//				if(mem2[p->m][p->n])
//				{
//					p->value = mem2[p->m][p->n];
//					head--;
//					continue;
//				}
			//	cout << "computing ackerman( " << p->m << " , " << p->n << " )\n";	
				(p->status)++;
				stk[head+1] = arr(p->m,p->n-1);
				head++;
				continue;
			}
			if( p->status == 1 )
			{
				(p->status)++;
				head++;
				stk[head] = arr(p->m-1, stk[head].value);
				continue;
			}
			if( p->status == 2 )
			{
				p->value = stk[head+1].value;
				mem2[p->m][p->n] = p->value;
				head--;	continue;
			}
		}
	}
	ans = stk[1].value;
	return ans;
}

int main()
{
	memset(mem,0,sizeof(mem));
	memset(mem2,0,sizeof(mem2));
	
	cout <<	Ackerman_dfs(3,3);
	
	cout <<	Ackerman_norm(3,3);
	
	return 0;
}
