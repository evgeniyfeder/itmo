/* Queue on array data structure class */
public class ArrayQueue {
  static private int beginSize = 16;                     /* Begin size of queue */
	
	private int head = 0; 								           /* First element of queue */
	private int tail = 0; 						 	 	           /* Last element of queue */
	private Object[] bulk = new Object[beginSize];  /* Memory for queue */

	/* Increase memory for bulk if we need place function */
	private void changeSize(int size) {
		if (size > bulk.length / 4 && size < bulk.length - 1)
			return;

		/* Alllocate new memory */
		int newSize = 0;
		if (size >= bulk.length - 1)	
			newSize = bulk.length * 2;
		else if (size <= bulk.length / 4)
			newSize = bulk.length / 2;
		
		Object[] newBulk = new Object[newSize];

		for (int i = 0; i < size; i++)
			newBulk[i] = bulk[(head + i) % bulk.length];
	
		/* Set new settings */
		bulk = newBulk;
		head = 0;
		tail = size;
	} /* End of 'changeSize' function */ 
	
	/* Add element to queue function */
	public void enqueue(Object elem) {
		changeSize(size());

		bulk[tail] = elem;
		tail = (tail + 1) % bulk.length;
	} /* End of 'enqueue' function */

	/* Get first element of queue function */
	public Object element() {
		if (size() == 0)
			return null;
		return bulk[head];
	} /* End of 'element' function */

	/* Delete and return first element in queue function */
	public Object dequeue() {
		if (size() == 0)
			return null;

		Object delElem = bulk[head];
		head = (head + 1) % bulk.length;
		changeSize(size());
	
		return delElem;
	} /* End of 'dequeue' function */

	/* Get size function */
	public int size() {
		return tail - head + (tail >= head ? 0: bulk.length);
	} /* End of 'size' function */

	/* Check for empty queue function */
	public boolean isEmpty() {
		return size() == 0;
	} /* End of 'isEmpty' function */

	/* Delete all elements from queue function */
	public void clear() {
		bulk = new Object[beginSize];
		head = 0;
		tail = 0;		
	} /* End of 'clear' function */ 
} /* End of 'ArrayQueue' class */