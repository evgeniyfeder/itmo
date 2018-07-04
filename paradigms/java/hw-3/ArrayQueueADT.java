/* Queue on array data structure class
 * INV: (size > 0 && queue[0...size - 1] != null) || size == 0
 */
public class ArrayQueueADT {
    private static int INITIAL_SIZE = 16;              /* Begin size of queue */

    private int head = 0;                              /* First element of queue */
    private int size = 0;                              /* Last element of queue */
    private Object[] bulk = new Object[INITIAL_SIZE];  /* Memory for queue */

    /* Increase memory for bulk if we need place function. */
    static private void changeSize(ArrayQueueADT queue) {
        if ((queue.size * 4 > queue.bulk.length && queue.size < queue.bulk.length) || queue.size < INITIAL_SIZE)
            return;

        /* Alllocate new memory */
        int newSize = 0;
        if (queue.size == queue.bulk.length) {
            newSize = queue.bulk.length * 2;
        } else if (queue.size * 4 <= queue.bulk.length) {
            newSize = queue.bulk.length / 2;
        }

        Object[] newBulk = new Object[newSize];

        int tail = (queue.head + queue.size - 1) % queue.bulk.length;
        if (queue.head < tail) {
            System.arraycopy(queue.bulk, queue.head, newBulk, 0, queue.size);
        } else {
            System.arraycopy(queue.bulk, queue.head, newBulk, 0, queue.bulk.length - queue.head);
            System.arraycopy(queue.bulk, 0, newBulk, queue.bulk.length - queue.head, tail + 1);
        }

        /* Set new settings */
        queue.bulk = newBulk;
        queue.head = 0;
    } /* End of 'changeSize' function */

    /* Add element to queue function
     * PRE: elem != null && queue != null
     * POST: queue[size] = elem && size` = size + 1 && other imutabled
     */
    static public void enqueue(ArrayQueueADT queue, Object elem) {
        queue.bulk[(queue.head + (queue.size++)) % queue.bulk.length] = elem;

        changeSize(queue);
    } /* End of 'enqueue' function */

    /* Get first element of queue function
     * PRE: size > 0 && queue != null
     * POST: R = queue[0] && all elements imutabled
     */
    static public Object element(ArrayQueueADT queue) {
        assert !isEmpty(queue);

        return queue.bulk[queue.head];
    } /* End of 'element' function */

    /* Get last element of queue function
     * PRE: size > 0 && queue != null
     * POST: R = queue[size - 1] && all elements imutabled
     */
    static public Object peek(ArrayQueueADT queue) {
        assert !isEmpty(queue);

        return queue.bulk[(queue.head + queue.size - 1) % queue.bulk.length];
    } /* End of 'peek' function */

    /* Delete and return first element in queue function
     * PRE: size > 0 && queue != null
     * POST: R = queue[0] && a[i] = a[i + 1] && size` = size - 1 && other imutabled
     */
    static public Object dequeue(ArrayQueueADT queue) {
        assert !isEmpty(queue);

        Object delElem = queue.bulk[queue.head];
        queue.bulk[queue.head] = null;
        queue.head = (queue.head + 1) % queue.bulk.length;
        --queue.size;
        changeSize(queue);

        return delElem;
    } /* End of 'dequeue' function */

    /* Add element to begin of queue
     * PRE: elem != null  && queue != null
     * POST: queue[i] = queue[i - 1](size >= i > 0) && queue[0] = elem && size` = size + 1 && other imutabled  
     */
    static public void push(ArrayQueueADT queue, Object elem) {
        queue.head = (queue.head - 1 + queue.bulk.length) % queue.bulk.length;
        queue.bulk[queue.head] = elem;

        ++queue.size;
        changeSize(queue);
    } /* End of 'push' function */

    /* Delete and return last element in queue function
     * PRE: size > 0  && queue != null
     * POST: R = queue[size - 1] && size` = size - 1 && other imutabled
     */
    static public Object remove(ArrayQueueADT queue) {
        assert !isEmpty(queue);

        Object delElem = queue.bulk[(queue.head + (--queue.size)) % queue.bulk.length];
        queue.bulk[(queue.head + queue.size) % queue.bulk.length] = null;
        changeSize(queue);

        return delElem;
    } /* End of 'remove' function */

    /* Get size function
     * PRE: True  && queue != null
     * POST: R = size && all imutabled
     */
    static public int size(ArrayQueueADT queue) {
        return queue.size;
    } /* End of 'size' function */

    /* Check for empty queue function
     * PRE: True && queue != null
     * POST: R = (size == 0) && all imutabled
     */
    static public boolean isEmpty(ArrayQueueADT queue) {
        return queue.size == 0;
    } /* End of 'isEmpty' function */

    /* Delete all elements from queue function
     * PRE: True && queue != null
     * POST: size = 0
     */
    static public void clear(ArrayQueueADT queue) {
        queue.bulk = new Object[INITIAL_SIZE];
        queue.head = 0;
        queue.size = 0;
    } /* End of 'clear' function */
} /* End of 'ArrayQueue' class */