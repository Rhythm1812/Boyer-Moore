#include <bits/stdc++.h>
using namespace std;
#define CHARSETSIZE 256 


//PreComputation for Bad Character Heuristic
vector<int> badCharacterPreComputation(string pattern)
{
	vector<int> badCharacterArray( CHARSETSIZE, -1);
	for(int i=0; i < pattern.size(); i++)
	{
 
		badCharacterArray[pattern[i]-65]=i;   
	}
	return badCharacterArray;
}


//PreComputation of shifts for Good Suffix Heuristic
vector<int> goodSuffixHeuristicPreComputation(string pattern)
{
	int m=pattern.size(); 
	int i=m, j=m+1;

	
	vector<int> borderPos(m+1), shifts(m+1,0); 
	
	borderPos[i]= j;
	
	while(i> 0)  
	{
		/*
			if character at position i-1 is not equal to 
          character at j-1, then continue searching to right 
          of the pattern. 
			*/
		while( j<=m && pattern[i-1]!= pattern[j-1])
		{
			/*
			The preceding character of matched string is diffent than
			mismatching character. 
			*/
			if(shifts[j]==0)
				shifts[j] = j-i;
			
			// update the position of next border
			j = borderPos[j]; 
		}
		/*As pattern[i-1] is equal to pattern[j-1], position of border 
		for prefix starting from  i-1 is j-1*/
		i--;
		j--;
		borderPos[i] = j;
	}
	/* calculated shift according to case1 i.e when full matched
	substring with different preceding charater exists in pattern*/
	
	/* now for case 2 i.e some suffix
	of matched string is found as prefix of pattern
	*/
	j= borderPos[0];
	for(i=0; i<=m; i++)
	{
		if(shifts[i] == 0)
			shifts[i] = j;
		if(i == j)
			j = borderPos[j];
	}
	return shifts;
}	


vector<int> BoyerMoore_Search(string text, string pattern)
{
	int i=0, j, m=pattern.size();
    int badShift,goodShift;
    //preprocessing
	vector<int> badCharacterArray= badCharacterPreComputation(pattern);
	vector<int> shifts= goodSuffixHeuristicPreComputation(pattern);
	vector<int> results;
	while(i <= text.size()-m)

	{
		j=m-1;
		while(j>=0 && pattern[j]==text[i+j])
			j--;

		if(j<0)
		{
			results.push_back(i);
			badShift= (i+m < text.size())? m - badCharacterArray[text[i+m]]: 1;
			goodShift = shifts[0];
			i+=max(badShift,goodShift); //max shift from both heuristic
		}
		else
		{
			badShift= max(1, j - badCharacterArray[text[i+j]]);
			goodShift = shifts[j+1];
			i+=max(badShift,goodShift); // max shift from both heuristic
		}

	}
	return results;
}

int main()
{
	string pattern, text;
	
	text="eptnpbkghtivzigsgsiqbbrukfsiklntoxrviggenjiqucmnuybwkkplbiujidmfgwhsxnfzhedobszztsifwizaeqlrirrnhfbeymawprltgwkyvtiqjkydjnonjtlftkgconxuovrbfawhredqbiqlfwkluivephhfkvzoftlnnowpvgqjeywljtebagohnumnawcdghpbstjynrxqsllebfopyovbndtjpingfpuijzceqsdkdynfvpzmipaftwkwxgvrtspauwbzhogmkhjpnnvqwuoyolpbtktykmvwqxgqnimuuxjpypnrdnttouokcpdtqjdwghrkjuvtsjqjywgqigehwqceuctsyorrffvgxtpxvdoajfugoqrbscgvlnvpkyfgixwdinryudxxdmxefqxjvroiugdgesxkhhnzbkxgprunrjyizjpoqzckiqfgekggibqobrzbalvexsldeayhaxdgghpvdygggrckaiervbhpbotaxxuylvhbmisyjacztdaiipmbflsrfxektwwnremydkxwzguxegzbdopyhwenuglxobyewvnoirwddsztjdmvsfjmijbp";

		pattern="wwnremy";
	
	vector<int> result= BoyerMoore_Search(text, pattern);
	if(result.size()==0)
		cout<<"Pattern is not found in given text!!\n";
	else
	{
		cout<<"Pattern is found at indices: ";
		for(int i=0; i< result.size(); i++)
			cout<< result[i] <<"Found at ";
	}
	return 0;
}