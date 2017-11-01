/* file: mu.h */
/** A minimal unit test framework taken from 
 *   http://www.jera.com/techinfo/jtns/jtn002.html
 */

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
extern int tests_run;
static char * all_tests(void);


int
main( int argc, const char ** argv )
{
     char * result = all_tests();

     if(result)
     {
	  printf("%s: Test failed: %s\nRun: %d\n", argv[0], result, tests_run);
     } else {
	  printf("%s: All tests passed. Run: %d\n", argv[0], tests_run);
     }

     return result != 0;
}
