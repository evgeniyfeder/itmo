/* Queue on list data structure class */
public class LinkedQueue extends AbstractQueue{

    /* One node declaration */
    private class Node {
        Object data;
        Node next, prev;

        /* Class constructor */
        public Node(Object data, Node prev, Node next) {
            this.data = data;
            this.next = next;
            this.prev = prev;
        } /* End of 'Node' constructor */
    } /* End of 'Node' class */
    Node head, tail;/* Begin and end of queue */

    /* Class constructor */
    public LinkedQueue() {
        clearEx();
    } /* End of 'LinkedQueue' constructor */

    /* Add element to begin of queue abstract function */
    protected void pushFront(Object elem) {
        Node newNode = new Node(elem, null, head);

        if (size == 0)
            head = tail = newNode;
        else {
            head.prev = newNode;
            head = newNode;
        }
    } /* End of 'pushFront' function */

    /* Delete element from begin of queue abstract function */
    protected void popFront() {
        if (size == 1)
            head = tail = null;
        else
            head = head.next;
    } /* End of 'popFront' function */

    /* Add element to end of queue abstract function */
    protected void pushBack(Object elem) {
        Node newNode = new Node(elem, tail, null);

        if (size == 0)
            head = tail = newNode;
        else {
            tail.next = newNode;
            tail = newNode;
        }
    } /* End of 'pushBack' function */

    /* Delete element from end of queue abstract function */
    protected void popBack() {
        if (size == 1)
            head = tail = null;
        else
            tail = tail.prev;
    } /* End of 'popBack' function */

    /* Clear queue abstract function */
    protected void clearEx() {
        head = new Node(null, null, null);
        tail = new Node(null, null, null);
    } /* End of 'clearEx' function */

    /* Get first element of queue function */
    public Object element() {
        return head.data;
    } /* End of 'element' function */

    /* Get last element of queue function */
    public Object peek() {
        return tail.data;
    } /* End of 'peek' function */

    /* Get empty queue of type function */
    protected Queue getEmptyQueue() {
        return new LinkedQueue();
    } /* End of 'getEmptyQueue' function */
} /* End of 'LinkedQueue' class */
