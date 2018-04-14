/**
 * Created by dzaba on 07.03.2017.
 */
public abstract class AbstractQueue implements Queue {
    /* Size of queue */
    protected int size = 0;

    /**** Virtual functions *****/
    /* Add element to begin of queue abstract function */
    protected abstract void pushFront(Object elem);

    /* Delete element from begin of queue abstract function */
    protected abstract void popFront();

    /* Add element to end of queue abstract function */
    protected abstract void pushBack(Object elem);

    /* Delete element from end of queue abstract function */
    protected abstract void popBack();

    /* Clear queue abstract function */
    protected abstract void clearEx();

    /***** Setting class functions *******/

    /* Add element to end of queue function */
    public void enqueue(Object elem) {
        pushBack(elem);
        size++;
    } /* End of 'enqueue' function */

    /* Delete and return first element in queue function */
    public Object dequeue() {
        assert !isEmpty();

        Object delElem = element();
        popFront();
        size--;

        return delElem;
    } /* End of 'dequeue' function */

    /* Add element to begin of queue */
    public void push(Object elem) {
        pushFront(elem);
        size++;
    } /* End of 'push' function */

    /* Delete and return last element in queue function */
    public Object remove() {
        assert !isEmpty();

        Object delElem = peek();
        popBack();
        size--;

        return delElem;
    } /* End of 'remove' function */

    /***** Getting class functions *******/
    /* Get size function */
    public int size() {
        return size;
    } /* Emd of 'size' function */

    /* Check for empty queue function */
    public boolean isEmpty() {
        return size == 0;
    } /* End of 'isEmpty' function */

    /* Delete all elements from queue function */
    public void clear() {
        clearEx();
        size = 0;
    } /* End of 'clearEx' function */
} /* End of 'AbstractQueue' class */
