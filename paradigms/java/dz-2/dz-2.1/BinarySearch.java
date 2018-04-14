/* The main class of programme */
public class BinarySearch {

	/* Iteration binary search 
	 * Pre: arr.length > 0 && arr[arr.length - 1] <= x && a[i] <= a[i - 1](0 < i < arr.length)
	 * Post: R = right && a[right - 1] < x <= a[right]
	 */
	public static int binarySearchIter(int[] arr, int x) {
		int left = -1, right = arr.length;

		/* Inv: 
		 * left < R && R <= right &&
		 * left' < R && R <= right' && 
		 * ((left` = left + (right - left) / 2 && right` = right) || 
     * (right` = left + (right - left) / 2 && left` = left))
		 */
		while (right - left > 1) {
			int middle = left + (right - left) / 2;

			if (x >= arr[middle]) {
				right = middle;				
			} else {
				left = middle;
			}
		}

		return right;
	} /* End of 'binarySearchIter' function */

	/* Recursive binary search 
	 * Pre: 
	 *   arr.length > 0 && arr[arr.length - 1] <= x && a[i] <= a[i - 1](0 <= i < arr.length) && 	 
	 * Post :
	 *   ((left` = left + (right - left) / 2 && right` = right) || 
   *   (right` = left + (right - left) / 2 && left` = left)) 
	 */
	public static int binarySearchRec(int[] arr, int left, int right, int x) {
		int middle = left + (right - left) / 2;

		if (right - left <= 1)
			return right;

		if (x >= arr[middle]) {
			return binarySearchRec(arr, left, middle, x);
		} else {
			return binarySearchRec(arr, middle, right, x);
		}
	} /* End of 'binarySearchRes' function */

	/* The main function of programme */
	public static void main(String[] args) {
		int x = Integer.parseInt(args[0]);
		int[] arr = new int[args.length - 1];
		
		/* Read input */		
		for (int i = 1; i < args.length; i++) {
			arr[i - 1] = Integer.parseInt(args[i]);		
		}

		//System.out.println(binarySearchRec(arr, -1, arr.length, x));
		System.out.println(binarySearchIterO(arr, x));
	} /* End of 'main' function */
} /* End of 'BinarySearch' class */
          