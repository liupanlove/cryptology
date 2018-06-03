#include<iostream>
#include<algorithm>
using namespace std;

int a[14] = {0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1};

int ans[15][15];
int l[15];

void show(int n, int l)
{
	cout << 1;
	for(int i = 1; i < l; ++i)
	{
		if(ans[n][i] != 0)
		cout << " + " << "x^" << i;
	}
	cout << endl;
 } 
void BM()
{
	cout << "step 0: ";// << ans[0][0] << endl;
	show(0, l[0]);
	cout << "l = " << l[0] << endl;
	
	
	for(int i = 0; i < 14; ++i)
	{
		cout << "step " << (i + 1) << ": ";// << endl;
		
		int tmp = 0;
		for(int j = 0, k = i; j <= l[i]; ++j, k--)
		{
			tmp += a[k] * ans[i][j];
			
		}
		
		//cout << "tmp: " << tmp << endl;
		
		if(tmp % 2 != 0) // ans²»±ä  l=0 
		{
			if(l[i] == 0)
			{
			//	cout << "ans[i+1][i+1] = " << ans[i + 1][i + 1] << endl; 
				ans[i + 1][i + 1] ++;
				ans[i + 1][i + 1] %= 2;
				
				ans[i + 1][0] = 1;
				l[i + 1] = i + 1;
			}
			else
			{
				int m;
				for(m = i; m > 0; m--)
				{
					if(l[m] > l[m - 1])
					{
						m--;
						break;
					}
				}
				
				l[i + 1] = max(l[i], i + 1 - l[i]);
				for(int j = 0; j < i - m; ++j) 
				{
					ans[i + 1][j] = ans[i][j];
				}
				
				for(int j = i - m; j <= l[i + 1]; ++j)
				{
					ans[i + 1][j] = ans[i][j] + ans[m][j - i + m];
					ans[i + 1][j] %= 2;
				}
			}
			
		}
		else
		{
			
			l[i + 1] = l[i];
			for(int j = 0; j <= l[i + 1]; ++j)
				ans[i + 1][j] = ans[i][j]; 
		}
		
		
		//for(int j = 0; j <= l[i + 1]; ++j) cout << ans[i + 1][j] << " "; 
		//cout << endl;
		show(i + 1, l[i + 1]);
		cout << "l = " << l[i + 1]<< endl;
	}
}

int main()
{
	for(int i = 0; i < 15; ++i)
		for(int j = 0; j < 15; ++j)
			ans[i][j] = 0; 
	
	ans[0][0] = 1;
	l[0] = 0;
	
	BM();
	return 0;
 } 
