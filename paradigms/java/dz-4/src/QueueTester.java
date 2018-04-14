/* Tester of queue */
public class QueueTester {
    /* Tester function */
    static public void test(Queue list, Queue arr, int size) {
        System.out.println("== TEST LIST QUEUE ==");
        for (int i = 0; i < size; i++) {
            System.out.println(i + " " + list.size() + " " + list.element() + " " + list.peek());
            list.push(i);
        }

        for (int i = 0; i < size; i++)
            System.out.println(list.dequeue() + " " + list.size());

        System.out.println("== TEST ARR QUEUE ==");
        for (int i = 0; i < size; i++) {
            System.out.println(i + " " + arr.size());
            arr.push(i);
        }

        for (int i = 0; i < size; i++)
            System.out.println(arr.dequeue() + " " + arr.size() + " " + arr.element() + " " + arr.peek());
    } /* End of 'test' function */

    /* Started point of the programme */
    static public void main(String[] args) {
        test(new LinkedQueue(), new ArrayQueue(), 50);
    } /* End of 'main' function */
}
