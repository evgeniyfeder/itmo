import java.util.function.Function;
import java.util.function.Predicate;

/* Queue interface
 * INV: (size > 0 && queue[0...size - 1] != null) || size == 0
 */
public interface Queue {
    /***** Setting class functions *******/

    /* Add element to end of queue function
     * PRE: elem != null && queue != null
     * POST: queue[size] = elem && size` = size + 1 && other imutabled
     */
    void enqueue(Object elem);

    /* Delete and return first element in queue function
     * PRE: size > 0
     * POST: R = queue[0] && queue[i] = queue[i + 1] && size` = size - 1 && other imutabled
     */
    Object dequeue();

    /* Add element to begin of queue
     * PRE: elem != null
     * POST: queue[i] = queue[i - 1](size >= i > 0) && queue[0] = elem && size` = size + 1 && other imutabled
     */
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

    /******* Modification *******/
    /* Create queue with elements like predicate
     * PRE: correct predicate && queue != null
     * POST: all imutabled && R = {R[0]...R[new_size] : new_size <= size && predicate(R[i]) = 1 && R - the same type of queue}
     * : && exist sequence i[0] ... i[k] (i[0] < ... < i[k]) : R[it] = queue[i[it]](0 <= it < k) && k - max
     */
    Queue filter(Predicate predicate);

    /* Create queue  with elements like predicate
     * PRE: correct function && queue != null
     * POST: all imutabled && R = {y[i] | y[i] = function(queue[i])} size(R) = size(queue) && R is the same type of queue
     */
    Queue map(Function function);
} /* End of 'Queue' class */
