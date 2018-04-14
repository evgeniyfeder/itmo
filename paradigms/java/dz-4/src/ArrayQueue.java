/* Queue on array data structure class */
public class ArrayQueue extends AbstractQueue {
	private int beginSize = 16;                       /* Begin size of queue */

	private int head = 0;				           /* First element of queue */
	private Object[] bulk = new Object[beginSize];  /* Memory for queue */

	/* Increase memory for bulk if we need place function. */
	private void changeSize(int queueSize) {
		if ((queueSize * 4 > bulk.length && queueSize < bulk.length) || queueSize < 16)
			return;

		/* Alllocate new memory */
		int newSize = 0;
		if (queueSize == bulk.length)
			newSize = bulk.length * 2;
		else if (queueSize * 4 <= bulk.length)
			newSize = bulk.length / 2;

		Object[] newBulk = new Object[newSize];

		int tail = (head + queueSize - 1) % bulk.length;
		if (head < tail) {
			System.arraycopy(bulk, head, newBulk, 0, queueSize);
		} else {
			System.arraycopy(bulk, head, newBulk, 0, bulk.length - head);
			System.arraycopy(bulk, 0, newBulk, bulk.length - head, tail + 1);
		}

		/* Set new settings */
		bulk = newBulk;
		head = 0;
	} /* End of 'changeSize' function */

	/* Add element to begin of queue abstract function */
	protected void pushFront(Object elem) {
		head = (head - 1 + bulk.length) % bulk.length;
		bulk[head] = elem;
		changeSize(size + 1);
	} /* End of 'pushFront' function */

	/* Delete element from begin of queue abstract function */
	protected void popFront() {
		bulk[head] = null;
		head = (head + 1) % bulk.length;
		changeSize(size - 1);
	} /* End of 'popFront' function */

	/* Add element to end of queue abstract function */
	protected void pushBack(Object elem) {
		bulk[(head + size) % bulk.length] = elem;
		changeSize(size + 1);
	} /* End of 'pushBack' function */

	/* Delete element from end of queue abstract function */
	protected void popBack() {
		bulk[(head + size - 1) % bulk.length] = null;
		changeSize(size - 1);
	} /* End of 'popBack' function */

	/* Clear queue abstract function */
	protected void clearEx() {
		bulk = new Object[beginSize];
		head = 0;
	} /* End of 'clearEx' function */

	/* Get first element of queue function */
	public Object element() {
		return bulk[head];
	} /* End of 'element' function */

	/* Get last element of queue function */
	public Object peek() {
		return bulk[(head + size - 1 + bulk.length) % bulk.length];
	} /* End of 'peek' function */
} /* End of 'ArrayQueue' class */