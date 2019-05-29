#define __must_check	__attribute__((warn_unused_result))
int __must_check foo()
{
	return 1;
}

// copy_to_user
int main()
{
	int ret;
	ret = foo();
	return 0;
}
