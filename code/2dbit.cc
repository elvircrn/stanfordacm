void updateBIT(int BIT[][N+1], int x, int y, int val) { 
	for (; x <= N; x += (x & -x)) { 
		// This loop update all the 1D BIT inside the 
		// array of 1D BIT = BIT[x] 
		for (; y <= N; y += (y & -y)) {
			BIT[x][y] += val; 
		}
	} 
	return; 
} 
// A function to get sum from (0, 0) to (x, y) 
int getSum(int BIT[][N+1], int x, int y) { 
	int sum = 0; 
	for(; x > 0; x -= x&-x) { 
		// This loop sum through all the 1D BIT 
		// inside the array of 1D BIT = BIT[x] 
		for(; y > 0; y -= y&-y) { 
			sum += BIT[x][y]; 
		} 
	} 
	return sum; 
} 
int getSum(int BIT[][N+1], int x1, int y1, int x2, int y2) { 
	return getSum(BIT, x2, y2)-getSum(BIT, x2, y1-1) - getSum(BIT, x1-1, y2)+getSum(BIT, x1-1, y1-1); 
}
