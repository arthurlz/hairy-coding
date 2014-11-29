void CalcNext(string str, int* next)
{
	next[0] = -1;
	int index, j;
	for(int i = 1 ; i < str.size(); i++)
	{
		j = i - 1;
		index = next[j];
		while( (index >= 0) && str[index] != str[j])
			index = next[index];

		if(index < 0)
			next[i] = 0;
		else
			next[i] = index + 1;
	}
}

int KMP(string g_s,string g_pattern,int *g_next)
{
	int ans = -1;
	int i = 0;
	int j = 0;
	int pattern_len = g_pattern.size();
	int n = g_s.size();
	CalcNext(g_pattern,g_next);
	while(i < n)
	{
		if(j == -1 || g_s[i] == g_pattern[j])
		{
			++i;
			++j;
		}
		else
			j = g_next[j];
		if(j == pattern_len)
		{
			ans = i - pattern_len;
			break;
		}
	}

	return ans;
}