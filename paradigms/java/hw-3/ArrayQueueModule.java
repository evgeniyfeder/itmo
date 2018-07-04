/* Queue on array data structure class 
 * INV: (size > 0 && queue[0...size - 1] != null) || size == 0
 */
public class ArrayQueueModule {
    private static int INITIAL_SIZE = 16;                  /* Begin size of queue */

    static private int head = 0;                           /* First element of queue */
    static private int size = 0;                           /* Last element of queue */
    static private Object[] bulk = new Object[INITIAL_SIZE];  /* Memory for queue */

    /* Increase memory for bulk if we need place function. */
    static private void changeSize() {
        if ((size * 4 > bulk.length && size < bulk.length) || size < INITIAL_SIZE)
            return;

        /* Alllocate new memory */
        int newSize = 0;
        if (size == bulk.length) {
            newSize = bulk.length * 2;
        } else if (size * 4 <= bulk.length) {
            newSize = bulk.length / 2;
        }

        Object[] newBulk = new Object[newSize];

        int tail = (head + size - 1) % bulk.length;
        if (head < tail) {
            System.arraycopy(bulk, head, newBulk, 0, size);
        } else {
            System.arraycopy(bulk, head, newBulk, 0, bulk.length - head);
            System.arraycopy(bulk, 0, newBulk, bulk.length - head, tail + 1);
        }
    
        /* Set new settings */
        bulk = newBulk;
        head = 0;
    } /* End of 'changeSize' function */

    /* Add element to queue function 
     * PRE: elem != null
     * POST: queue[size] = elem && size` = size + 1 && other imutabled
     */
    static public void enqueue(Object elem) {
        bulk[(head + (size++)) % bulk.length] = elem;

        changeSize();
    } /* End of 'enqueue' function */

    /* Get first element of queue function 
     * PRE: size > 0
     * POST: R = queue[0] && all elements imutabled
     */
    static public Object element() {
        assert !isEmpty();

        return bulk[head];
    } /* End of 'element' function */

    /* Get last element of queue function 
     * PRE: size > 0
     * POST: R = queue[size - 1] && all elements imutabled
     */
    static public Object peek() {
        assert !isEmpty();

        return bulk[(head + size - 1) % bulk.length];
    } /* End of 'peek' function */

    /* Delete and return first element in queue function 
     * PRE: size > 0
     * POST: R = queue[0] && a[i] = a[i + 1] && size` = size - 1 && other imutabled
     */
    static public Object dequeue() {
        assert !isEmpty();

        Object delElem = bulk[head];
        bulk[head] = null;
        head = (head + 1) % bulk.length;
        --size;
        changeSize();

        return delElem;
    } /* End of 'dequeue' function */

    /* Add element to begin of queue
     * PRE: elem != null
   * POST: queue[i] = queue[i - 1](size >= i > 0) && queue[0] = elem && size` = size + 1 && other imutabled */
    static public void push(Object elem) {
        head = (head - 1 + bulk.length) % bulk.length;
        bulk[head] = elem;

        ++size;
        changeSize();
    } /* End of 'push' function */

    /* Delete and return last element in queue function 
     * PRE: size > 0
     * POST: R = queue[size - 1] && size` = size - 1 && other imutabled
     */
    static public Object remove() {
        assert !isEmpty();

        Object delElem = bulk[(head + (--size)) % bulk.length];
        bulk[(head + size) % bulk.length] = null;
        changeSize();

        return delElem;
    } /* End of 'remove' function */

    /* Get size function 
     * PRE: True
     * POST: R = size && all imutabled
     */
    static public int size() {
        return size;
    } /* End of 'size' function */

    /* Check for empty queue function 
     * PRE: True
     * POST: R = (size == 0) && all imutabled 
     */
    static public boolean isEmpty() {
        return size == 0;
    } /* End of 'isEmpty' function */

    /* Delete all elements from queue function
     * PRE: True
     * POST: size = 0
     */
    static public void clear() {
        bulk = new Object[INITIAL_SIZE];
        head = 0;
        size = 0;
    } /* End of 'clear' function */
} /* End of 'ArrayQueue' class */