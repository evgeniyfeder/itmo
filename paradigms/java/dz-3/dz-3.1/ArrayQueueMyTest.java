/* Tester for array queuq class */
public class ArrayQueueMyTest {
	/* Tests for array queue function */
	public static void test(int size) {
		ArrayQueue queue = new ArrayQueue();

		for (int i = 0; i < size; i++)
			queue.enqueue(i);

		for (int i = 0; i < size; i++)
			System.out.printf("%d ", queue.dequeue()); 
	} /* End of 'test' function */

	/* The main function of programme */
	public static void main(String[] args) {
		test(100);
	} /* End of 'main' function */
} /* End of 'ArrayQueueMyTest' class */