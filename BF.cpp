int BFMatch(char *s,char *p) 
{ 
	int i,j; 
	i=0; 
	while(i<strlen(s)) 
	{ 
		j=0; 
		while(s[i]==p[j]&&j<strlen(p)) 
		{ 
			i++; 
			j++; 
		} 
		if(j==strlen(p)) 
			return i-strlen(p); 
		i=i-j+1;                //Ö¸Õëi»ØËÝ 
	} 
	return -1;   
}