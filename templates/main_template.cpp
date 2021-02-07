#include <unistd.h>
// #include "006_Extract_Numbers/problem_06.hpp"
#include "008_Correct_Parenthesis/problem_08.hpp"
// #include "011_Count_Numbers/problem_11.hpp"
// #include "012_Count_Numbers_fast/problem_12.hpp"
// #include "013_Most_Frequent_Number/problem_13.hpp"
// #include "014_Reversed_Prime/problem_14.hpp"
// #include "015_Count_Prime_Numbers/problem_15.hpp"
// #include "016_Anagram/problem_16.hpp"

int main()
{
#ifdef DEBUG_MODE
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);

	if (access("input11.txt", F_OK) == -1)
		printf("file 11 not exists\n");
	if (access("input12.txt", F_OK) == -1)
		printf("file 12 not exists\n");
#endif
	problem_08();
	return 0;
}
