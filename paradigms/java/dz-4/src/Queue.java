/* Queue interface
 * INV: size >= 0 && queue[0...size] != null
 */
public interface Queue {
    /***** Setting class functions *******/

    /* Add element to end of queue function
     * PRE: True
     * POST: queue[size] = elem && size` = size + 1 && other imutabled
     */
    void enqueue(Object elem);

    /* Delete and return first element in queue function
     * PRE: size > 0
     * POST: R = queue[0] && a[i] = a[i + 1] && size` = size - 1 && other imutabled
     */
    Object dequeue();

    /* Add element to begin of queue
     * PRE: True
     * POST: queue[i] = queue[i - 1](size >= i > 0) && queue[0] = elem && size` = size + 1  */
    void push(Object elem);

    /* Delete and return last element in queue function
     * PRE: size > 0
     * POST: R = queue[size - 1] && size` = size - 1 && other imutabled
     */
    Object remove();

    /***** Getting class functions *******/

    /* Get first element of queue function
     * PRE: size > 0
     * POST: R = queue[0] && all elements imutabled
     */
    Object element();

    /* Get last element of queue function
     * PRE: size > 0
     * POST: R = queue[size - 1] && all elements imutabled
     */
    Object peek();

    /* Get size function
     * PRE: True
     * POST: R = size && all imutabled
     */
    int size();

    /* Check for empty queue function
     * PRE: True
     * POST: R = (size == 0) && all imutabled
     */
    boolean isEmpty();

    /* Delete all elements from queue function
     * PRE: True
     * POST: size = 0
     */
    void clear();
} /* End of 'Queue' class */
