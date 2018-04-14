/* Queue on array data structure class */
public class ArrayQueueADT {
  static private int beginSize = 16;                     /* Begin size of queue */
	
	private int head = 0; 								           /* First element of queue */
	private int tail = 0; 						 	 	           /* Last element of queue */
	private Object[] bulk = new Object[beginSize];  /* Memory for queue */

	/* Increase memory for queue.bulk if we need place function */
	static private void changeSize(ArrayQueueADT queue, int size) {
		if (size > queue.bulk.length / 4 && size < queue.bulk.length - 1)
			return;

		/* Alllocate new memory */
		int newSize = 0;
		if (size >= queue.bulk.length - 1)	
			newSize = queue.bulk.length * 2;
		else if (size <= queue.bulk.length / 4)
			newSize = queue.bulk.length / 2;
		
		Object[] newBulk = new Object[newSize];

		for (int i = 0; i < size; i++)
			newBulk[i] = queue.bulk[(queue.head + i) % queue.bulk.length];
	
		/* Set new settings */
		queue.bulk = newBulk;
		queue.head = 0;
		queue.tail = size;
	} /* End of 'incSize' function */ 
	
	/* Decrease memory for queue.bulk if we need it 

	/* Add element to queue function */
	static public void enqueue(ArrayQueueADT queue, Object elem) {
		changeSize(queue, size(queue));

		queue.bulk[queue.tail] = elem;
		queue.tail = (queue.tail + 1) % queue.bulk.length;
	} /* End of 'enqueue' function */

	/* Get first element of queue function */
	static public Object element(ArrayQueueADT queue) {
		if (size(queue) == 0)
			return null;
		return queue.bulk[queue.head];
	} /* End of 'element' function */

	/* Delete and return first element in queue function */
	static public Object dequeue(ArrayQueueADT queue) {
		if (size(queue) == 0)
			return null;

		Object delElem = queue.bulk[queue.head];
		queue.head = (queue.head + 1) % queue.bulk.length;
		changeSize(queue, size(queue));

		return delElem;
	} /* End of 'dequeue' function */

	/* Get size function */
	static public int size(ArrayQueueADT queue) {
		return queue.tail - queue.head + (queue.tail >= queue.head ? 0: queue.bulk.length);
	} /* End of 'size' function */

	/* Check for empty queue function */
	static public boolean isEmpty(ArrayQueueADT queue) {
		return size(queue) == 0;
	} /* End of 'isEmpty' function */

	/* Delete all elements from queue function */
	static public void clear(ArrayQueueADT queue) {
		queue.bulk = new Object[beginSize];
		queue.head = 0;
		queue.tail = 0;		
	} /* End of 'clear' function */ 
} /* End of 'ArrayQueue' class */