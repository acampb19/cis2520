# include <stdio.h>

/*function to print out all permutations of CARBON*/
int carbon(void)
{
	char string[5]; /*string to store all permutations*/
	int i, j, k, m, n, p; /*integers for loops*/
	
	/*first loop for first letter*/
	for(i = 0; i < 6; i++)
	{
		if(i == 0)
		{
			/*appends C to string*/
			string[0] = 'C';
		}
		else if(i == 1)
		{
			/*appends A to string*/
			string[0] = 'A';
		}
		else if(i==2)
		{
			/*appends R to string*/
			string[0] = 'R';
		}
		else if(i==3)
		{
			/*appends B to string*/
			string[0] = 'B';
		}
		else if(i==4)
		{
			/*appends O to string*/
			string[0] = 'O';
		}
		else if(i==5)
		{
			/*appends N to string*/
			string[0] = 'N';
		}
		
		/*loop for 2nd letter*/
		for(j=0; j<6;j++)
		{
			if(j==0)
			{
				/*appends C if first letter is not C*/
				if(string[0] != 'C')
				{
					string[1] = 'C';
				}
				else
				{
					/*goes to next letter if first letter is C*/
					j++;
				}

			}
			if(j==1)
			{
				/*appends A if first letter is not A*/
				if(string[0] != 'A')
				{
					string[1] = 'A';
				}
				else
				{
					/*goes to next letter if first letter is A*/
					j++;
				}
			}
			if(j==2)
			{
				/*appends R if first letter is not R*/
				if(string[0] != 'R')
				{
					string[1] = 'R';
				}
				else
				{
					/*goes to next letter if first letter is R*/
					j++;
				}
			}
			if(j==3)
			{
				/*appends B if first letter is not B*/
				if(string[0] != 'B')
				{
					string[1] = 'B';
				}
				else
				{
					/*goes to next letter if first letter is B*/
					j++;
				}
			}
			if(j==4)
			{
				/*appends O if first letter is not O*/
				if(string[0] != 'O')
				{
					string[1] = 'O';
				}
				else
				{
					/*goes to next letter if first letter is O*/
					j++;
				}

			}
			if(j==5)
			{
				/*appends N if first letter is not N*/
				if(string[0] != 'N')
				{
					string[1] = 'N';
				}
				else
				{
					/*goes to next letter if first letter is N*/
					j++;
				}
			}
			if(j==6)
			{
				/*exits loop if all letters have been used*/
				continue;
			}
			
			/*loop for 3rd letter*/
			for(m=0; m<6;m++)
			{
				if(m==0)
				{
					/*appends C if C has not been used*/
					if(string[0] != 'C'&& string[1] != 'C')
					{
						string[2] = 'C';
					}
					else
					{
						/*goes to next letter if C has already been used*/
						m++;
					}
	
				}
				if(m==1)
				{
					/*appends A if A has not been used*/
					if(string[0] != 'A'&& string[1] != 'A')
					{
						string[2] = 'A';
					}
					else
					{
						/*goes to next letter if A has already been used*/
						m++;
					}
				}
				if(m==2)
				{	
					/*appends R if R has not been used*/
					if(string[0] != 'R'&& string[1] != 'R')
					{
						string[2] = 'R';
					}
					else
					{
						/*goes to next letter if R has already been used*/
						m++;
					}
				}
				if(m==3)
				{
					/*appends B if B has not been used*/
					if(string[0] != 'B'&& string[1] != 'B')
					{
						string[2] = 'B';
					}
					else
					{
						/*goes to next letter if B has already been used*/
						m++;
					}
				}
				if(m==4)
				{
					/*appends O if O has not been used*/
					if(string[0] != 'O'&& string[1] != 'O')
					{
						string[2] = 'O';
					}
					else
					{
						/*goes to next letter if O has already been used*/
						m++;
					}
				}
				if(m==5)
				{
					/*appends N if N has not been used*/
					if(string[0] != 'N'&& string[1] != 'N')
					{
						string[2] = 'N';
					}
					else
					{
						/*goes to next letter if N has already been used*/
						m++;
					}
				}
				if(m==6)
				{
					/*exits loop if all letters have been used*/
					continue;
				}
				
				/*loop for 4th letter*/	
				for(n=0; n<6;n++)
				{
					if(n==0)
					{
						/*appends C if C has not been used*/
						if(string[0] != 'C' && string[1] != 'C' && string[2] != 'C')
						{
							string[3] = 'C';
						}
						else
						{
							/*goes to next letter if C has already been used*/
							n++;
						}
		
					}
					if(n==1)
					{
						/*appends A if A has not been used*/
						if(string[0] != 'A' && string[1] != 'A' && string[2] != 'A')
						{
							string[3] = 'A';
						}
						else
						{
							/*goes to next letter if A has already been used*/
							n++;
						}
					}
					if(n==2)
					{	
						/*appends R if R has not been used*/
						if(string[0] != 'R' && string[1] != 'R' && string[2] != 'R')
						{
							string[3] = 'R';
						}
						else
						{
							/*goes to next letter if R has already been used*/
							n++;
						}
					}
					if(n==3)
					{	
						/*appends B if B has not been used*/
						if(string[0] != 'B' && string[1] != 'B' && string[2] != 'B')
						{
							string[3] = 'B';
						}
						else
						{
							/*goes to next letter if B has already been used*/
							n++;
						}
					}				
					if(n==4)
					{	
						/*appends O if O has not been used*/
						if(string[0] != 'O' && string[1] != 'O' && string[2] != 'O')
						{
							string[3] = 'O';
						}
						else
						{
							/*goes to next letter if O has already been used*/
							n++;
						}
					}
					if(n==5)
					{
						/*appends N if N has not been used*/
						if(string[0] != 'N' && string[1] != 'N' && string[2] != 'N')
						{
							string[3] = 'N';
						}
						else
						{
							/*goes to next letter if N has already been used*/
							n++;
						}
					}
					if(n==6)
					{
						/*exits loop if all letters have been used*/
						continue;
					}


					for(p=0; p<6;p++)
					{
						if(p==0)
						{
							/*appends C if C has not been used*/
							if(string[0] != 'C' && string[1] != 'C' && string[2] != 'C' && string[3] != 'C')
							{
								string[4] = 'C';
							}
							else
							{
								/*goes to next letter if C has already been used*/
								p++;
							}
			
						}
						if(p==1)
						{
							/*appends A if A has not been used*/
							if(string[0] != 'A' && string[1] != 'A' && string[2] != 'A' && string[3] != 'A')
							{
								string[4] = 'A';
							}
							else
							{
								/*goes to next letter if A has already been used*/
								p++;
							}
						}
						if(p==2)
						{	
							/*appends R if R has not been used*/
							if(string[0] != 'R' && string[1] != 'R' && string[2] != 'R' && string[3] != 'R')
							{
								string[4] = 'R';
							}
							else
							{
								/*goes to next letter if R has already been used*/
								p++;
							}
						}	
						if(p==3)
						{	
							/*appends B if B has not been used*/
							if(string[0] != 'B'&& string[1] != 'B'&& string[2] != 'B'&& string[3] != 'B')
							{
								string[4] = 'B';
							}
							else
							{
								/*goes to next letter if B has already been used*/
								p++;
							}
						}				
						if(p==4)
						{	
							/*appends O if O has not been used*/
							if(string[0] != 'O'&& string[1] != 'O'&& string[2] != 'O'&& string[3] != 'O')
							{
								string[4] = 'O';
							}
							else
							{
								/*goes to next letter if O has already been used*/
								p++;
							}
						}
						if(p==5)
						{
							/*appends N if N has not been used*/
							if(string[0] != 'N'&& string[1] != 'N'&& string[2] != 'N'&& string[3] != 'N')
							{
								string[4] = 'N';
							}
						}
						for(k=0;k<1;k++)
						{
							/*appends C if C has not been used*/
							if(string[0] != 'C' && string[1] != 'C' && string[2] != 'C' && string[3] != 'C' && string[4] != 'C' && string[5] != 'C')
							{
								string[5] = 'C';
								printf("%s\n", string);
							}
							/*appends A if A has not been used*/
							else if(string[0] != 'A' && string[1] != 'A' && string[2] != 'A' && string[3] != 'A' && string[4] != 'A' && string[5] != 'A')
							{
								string[5] = 'A';
								printf("%s\n", string);
							}	
							/*appends R if R has not been used*/
							else if(string[0] != 'R' && string[1] != 'R' && string[2] != 'R' && string[3] != 'R' && string[4] != 'R' && string[5] != 'R')
							{
								string[5] = 'R';
								printf("%s\n", string);
							}	
							/*appends B if B has not been used*/
							else if(string[0] != 'B' && string[1] != 'B' && string[2] != 'B' && string[3] != 'B' && string[4] != 'B' && string[5] != 'B')
							{
								string[5] = 'B';
								printf("%s\n", string);
							}
							/*appends O if O has not been used*/
							else if(string[0] != 'O' && string[1] != 'O' && string[2] != 'O' && string[3] != 'O' && string[4] != 'O' && string[5] != 'O')
							{
								string[5] = 'O';
								printf("%s\n", string);
							}					
							/*appends N if N has not been used*/
							else if(string[0] != 'N' && string[1] != 'N' && string[2] != 'N' && string[3] != 'N' && string[4] != 'N' && string[5] != 'N')
							{
								string[5] = 'N';
								printf("%s\n", string);
							}
						}
					}
				}
			}
		}
	}
return 0;
}

