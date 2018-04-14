/* Queue on array data structure class 
 * INV: size >= 0 &&
 *   head <= tail => bulk[head]...bulk[tail - 1] != null &&
 *   head > tail => (bulk[head]...bulk[size - 1] != null && bulk[0]...bulk[tail - 1] != null)
 */
public class ArrayQueueModule {
  static private int beginSize = 16;                     /* Begin size of queue */
	
	static private int head = 0; 								           /* First element of queue */
	static private int tail = 0; 						 	 	           /* Last element of queue */
	static private Object[] bulk = new Object[beginSize];  /* Memory for queue */

	/* Increase memory for bulk if we need place function.
	 * PRE: size >= 0
	 * POST: 
	 * (head = 0 && tail = size && 
	 *  size <= bulk.length => bulk.length /= 2 &&
	 *  size >= bulk.length - 1 => bulk.length *= 2 && 
	 *	bulk`[0...size] = bulk[head...(head + size) % bulk.length]) &&
	 *  (size > bulk.length / 4 && size < bulk.length - 1) => bulk.length = bulk.length
	 */
	static private void changeSize(int size) {
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

	/* Add element to queue function 
	 * PRE: True
	 * POST: last element of queue = elem && size` = size + 1 && other imutabled
	 */
	static public void enqueue(Object elem) {
		changeSize(size());

		bulk[tail] = elem;
		tail = (tail + 1) % bulk.length;
	} /* End of 'enqueue' function */

	/* Get first element of queue function 
	 * PRE: size > 0
	 * POST: R = first element of queue && all elements imutabled
	 */
	static public Object element() {
		assert !isEmpty();

		return bulk[head];
	} /* End of 'element' function */

	/* Delete and return first element in queue function 
	 * PRE: size > 0
	 * POST: R = first element of queue && a[i] = a[i + 1] && size` = size - 1 && other imutabled
	 */
	static public Object dequeue() {
		assert !isEmpty();

		Object delElem = bulk[head];
		head = (head + 1) % bulk.length;
		changeSize(size());
	
		return delElem;
	} /* End of 'dequeue' function */

	/* Get size function 
	 * PRE: True
	 * POST: R = size of queue && all imutabled
	 */
	static public int size() {
		return tail - head + (tail >= head ? 0: bulk.length);
	} /* End of 'size' function */

	/* Check for empty queue function 
	 * PRE: True
	 * POST: R = (size == 0) && all imutabled 
	 */
	static public boolean isEmpty() {
		return size() == 0;
	} /* End of 'isEmpty' function */

	/* Delete all elements from queue function
   * PRE: True
	 * POST: size = 0
   */
	static public void clear() {
		bulk = new Object[beginSize];
		head = 0;
		tail = 0;		
	} /* End of 'clear' function */ 
} /* End of 'ArrayQueue' class */