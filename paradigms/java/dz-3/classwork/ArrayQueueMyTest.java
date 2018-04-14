/* Tester for array queuq class */
public class ArrayQueueMyTest {
	/* Tests for array queue function */
	public static void test(int size) {
		for (int i = 0; i < size; i++) {
			System.out.println(i + " " + ArrayQueueModule.size()); 
			ArrayQueueModule.push(i);
		}

		for (int i = 0; i < size; i++)
			System.out.println(ArrayQueueModule.dequeue() + " " + ArrayQueueModule.size());
	} /* End of 'test' function */

	/* The main function of programme */
	public static void main(String[] args) {
		test(100);
	} /* End of 'main' function */
} /* End of 'ArrayQueueMyTest' class */