/* The main class of programme */
public class BinarySearch {

	/* Iteration binary search 
	 * Pre: 
   * arr[-1] = inf && arr[arr.length] = -inf &&
	 * arr[i] <= arr[i - 1](0 <= i < arr.length)
	 * Post: R = right && arr[right - 1] > x >= arr[right]
	 */
	public static int binarySearchIter(int[] arr, int x) {
		int left = -1, right = arr.length;

		/* Inv: 
				right` - left` < right - left && 
				arr[left`] > x >= arr[right`]
		 */
		while (right - left > 1) {
			// Inv && right - left > 1
			int middle = left + (right - left) / 2;

			// Inv && right - left > 1 && left < middle < right
			if (x >= arr[middle]) {
				// Inv && right - left > 1 && left < middle < right && x >= arr[middle]
				right = middle;
				// Inv && right - left > 1 && right` = middle && arr[left] > x >= arr[right`]				
			} else {
				// Inv && right - left > 1 && left < middle < right && x < arr[middle]
				left = middle;
				// Inv && right - left > 1 && left` = middle && arr[left`] > x >= arr[right]				
			}
			// left < middle < right => right` - left` < right - left 
		}

		/* Post: 
		 *	Inv && right - left == 1 => 
		 *	right = left - 1 => 
		 * 	R = right && arr[right - 1] > R > arr[right]
     */
		return right;
	} /* End of 'binarySearchIter' function */
	
	/* Recursive binary search starter */
	public static int binarySearchRec(int[] arr, int x) {
		return binarySearchRec(arr, -1, arr.length, x);
	} /* End of 'binarySearchRec' function */

	/* Recursive binary search function 
	 * Pre: 
	 * arr[-1] = inf && arr[arr.length] = -inf &&  
	 * a[i] <= a[i - 1](0 < i < arr.length) 	 
	 * Post:
	 *   R = right && arr[right - 1] > x >= arr[right]
	 * Inv:
	 * right` - left` < right - left && arr[left`] < x <= arr[right`]	
	 */
	public static int binarySearchRec(int[] arr, int left, int right, int x) {
		if (right - left <= 1) {
			/* Post: 
		   *	Inv && right - left == 1 => 
		   *	right = left - 1 => 
		   * 	R = right && arr[right - 1] > R >= arr[right]
       */
			return right;
		}
		
		int middle = left + (right - left) / 2;
		// left < middle < right
		
		if (x >= arr[middle]) {
			// Inv && right - left > 1 && left < middle < right && x >= arr[middle] && arr[0]...arr[left] > x >= arr[middle]
			return binarySearchRec(arr, left, middle, x);
		} else {
			// Inv && right - left > 1 && left < middle < right && x < arr[middle] && arr[0]...arr[middle] > x >= arr[right]				
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
          