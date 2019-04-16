- example to show the style of a function
	```
	/*
	 * str_has_prefix - Test if a string has a given prefix
	 * @str: The string to test
	 * @prefix: The string to see if @str starts with
	 *
	 * A common way to test a prefix of a string is to do:
	 *  strncmp(str, prefix, sizeof(prefix) - 1)
	 *
	 * But this can lead to bugs due to typos, or if prefix is a pointer
	 * and not a constant. Instead use str_has_prefix().
	 *
	 * Returns: 0 if @str does not start with @prefix
			 strlen(@prefix) if @str does start with @prefix
	 */
	static __always_inline size_t str_has_prefix(const char *str, const char *prefix)
	{
		size_t len = strlen(prefix);
		return strncmp(str, prefix, len) == 0 ? len : 0;
	}
	```

- some remind of string
	```
    char s[]="123";
    printf("%d\n", (int)sizeof(s));     /* 4 */
    printf("%d\n", (int)strlen(s));     /* 3 */

    char d[10]="123";
    printf("%d\n", (int)sizeof(d));     /* 10 */
    printf("%d\n", (int)strlen(d));     /* 3 */
    if(d[4]+d[5]+d[6]+d[7]+d[8]+d[9] == 0) printf("yes\n");     /* yes */
    
    char *p=d;
    printf("%d\n", (int)sizeof(p));     /* 8 */
    printf("%d\n", (int)strlen(p));     /* 3 */
	```
