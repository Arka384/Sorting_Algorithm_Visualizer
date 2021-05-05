#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#define SIZE 155	//155	//315
#define BlockSize 6	//6		//6
#define Gap BlockSize+8	//8	//4
#define ArrayLimit 600
#define SleepTime 100

using namespace sf;

//printing functions
void PrintInit(RenderWindow &);
void Insertion_Print(RenderWindow & ,int ,int );
void Bubble_Print(RenderWindow & ,int );
void Selection_Print(RenderWindow & ,int ,int );
void Shell_Print(RenderWindow &, int , int );
void Merge_Print(RenderWindow & ,int , int );
void Quick_Print(RenderWindow &, int , int );
void Radix_Print(RenderWindow &, int );
void Cocktail_Print(RenderWindow & , int ,int );
void Heap_Print(RenderWindow &, int);

//sorting functions
void mergesort(int[], int, int, RenderWindow &);
void merge(int[], int, int, int);
void quick_sort(int[], int, int, RenderWindow &);
int find_pivot(int[], int, int, RenderWindow &);
int largest(int[], int);
void Radix_sort(int[], int , RenderWindow & );
void Cocktail_Sort(int[], int, RenderWindow & );
void create_heap(int[], int, int);
void HeapSort(int[], int , RenderWindow & );

int array[SIZE];
int width = 158, height = 35;
int sortNumber = 0;

int main()
{
	int i,j;
	int choice;
	srand(time(NULL));
	RenderWindow window(VideoMode(1280, 800), "Test", Style::Default);

	for (i = 0; i < SIZE; i++)
		array[i] = rand() % ArrayLimit;

	while (window.isOpen())
	{
		Event evnt;

		while (window.pollEvent(evnt))
		{
			int c, t, m;
			int index = 3, k = 0;

			switch (evnt.type)
			{
				case Event::Closed:
					window.close();
				default:
					break;

			}

			switch (sortNumber)
			{
			case 0:
				PrintInit(window);
				break;

			case 1:
				// Code for insertion sort
				for (i = 1; i < SIZE; i++)
				{
					c = i - 1;
					t = array[i];
					while (array[c] > t && c >= 0)
					{
						array[c + 1] = array[c];
						c = c - 1;
					}
					array[c + 1] = t;
					Insertion_Print(window, i, t);
					sleep(milliseconds(SleepTime));
				}
				sleep(seconds(1));
				sortNumber = 0;
				break;

			case 2:
				//code for bubble sort
				for (i = 0; i < SIZE; i++)
				{
					for (j = 0; j < SIZE - i - 1; j++)
					{
						if (array[j] > array[j + 1])
						{
							t = array[j];
							array[j] = array[j + 1];
							array[j + 1] = t;
						}
					}
					Bubble_Print(window, j);
					sleep(milliseconds(SleepTime));
				}
				sleep(seconds(1));
				sortNumber = 0;
				break;

			case 3:
				//code for selection sort
				for (i = 0; i < SIZE - 1; i++)
				{
					m = i;
					for (j = i + 1; j < SIZE; j++)
					{
						if (array[m] > array[j])
							m = j;
					}
					if (i != m)
					{
						t = array[i];
						array[i] = array[m];
						array[m] = t;
					}
					Selection_Print(window, i, m);
					sleep(milliseconds(SleepTime));
				}
				sleep(seconds(1));
				sortNumber = 0;
				break;

			case 4:
				//code for shell sort
				while (index >= 1)
				{
					for (i = index; i < SIZE; i++)
					{
						k = array[i];
						for (j = i - index; j >= 0 && array[j] > k; j = j - index)
							array[j + index] = array[j];

						array[j + index] = k;

						Shell_Print(window, i, k);
						sleep(milliseconds(SleepTime));
					}
					index--;
				}
				sleep(seconds(1));
				sortNumber = 0;
				break;

			case 5:
				mergesort(array, 0, SIZE - 1, window);

				sleep(seconds(1));
				sortNumber = 0;
				break;

			case 6:
				quick_sort(array, 0, SIZE - 1, window);

				sleep(seconds(1));
				sortNumber = 0;
				break;

			case 7:
				Radix_sort(array, SIZE, window);
				sleep(seconds(1));
				sortNumber = 0;
				break;

			case 8:
				Cocktail_Sort(array, SIZE, window);
				sleep(seconds(1));
				sortNumber = 0;
				break;

			case 9:
				HeapSort(array, SIZE, window);
				sleep(seconds(1));
				sortNumber = 0;
				break;

			default:
				break;
			}
		}
		
	}
}

// sorting functions 

void mergesort(int a[], int beg, int end, RenderWindow &thisWindow)
{
	int mid;
	if (beg != end)
	{
		mid = (beg + end) / 2;
		mergesort(a, beg, mid, thisWindow);
		Merge_Print(thisWindow, beg, mid);
		sleep(milliseconds(SleepTime-50));
		mergesort(a, mid + 1, end, thisWindow);
		Merge_Print(thisWindow, mid+1, end);
		sleep(milliseconds(SleepTime));
		merge(a, beg, mid, end);
	}
}

void merge(int a[], int top, int size, int bottom)
{
	int f, t, s, temp[SIZE], upper, i;
	f = top;
	s = size + 1;
	t = top;
	sleep(milliseconds(100));
	while ((f <= size) && (s <= bottom))
	{
		if (a[f] <= a[s])
		{
			temp[t] = a[f];
			f++;
		}
		else
		{
			temp[t] = a[s];
			s++;
		}
		t++;
	}
	if (f <= size)
	{
		for (i = f; i <= size; i++)
		{
			temp[t] = a[i];
			t++;
		}
	}
	else
	{
		for (i = s; i <= bottom; i++)
		{
			temp[t] = a[i];
			t++;
		}
	}
	for (upper = top; upper <= bottom; upper++)
		a[upper] = temp[upper];
}


void quick_sort(int arr[], int l, int u, RenderWindow &thisWindow)
{
	int pivot;
	if (l >= u)
		return;
	pivot = find_pivot(arr, l, u, thisWindow);

	quick_sort(arr, l, pivot - 1, thisWindow);
	
	quick_sort(arr, pivot + 1, u, thisWindow);
	
}

int find_pivot(int arr[], int l, int u, RenderWindow &thisWindow)
{
	int i = l + 1, j = u, temp = 0, pivot = arr[l];
	while (i <= j)
	{
		while (arr[i] < pivot && i < u)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
		else
			i++;
		Quick_Print(thisWindow, l, u);
		sleep(milliseconds(SleepTime));
	}
	arr[l] = arr[j];
	arr[j] = pivot;
	return j;
}

void Radix_sort(int ar[], int n, RenderWindow &thisWindow)
{
	int maxD = 0, pass = 0, i, j, k, modVal = 1, rem;
	int bucket[10][SIZE] = { 0 };
	int bucket_index[10] = { 0 };

	int large = largest(ar, n);

	while (large > 0)
	{
		maxD++;
		large /= 10;
	}

	for (pass = 0; pass < maxD; pass++) 
	{
		for (i = 0; i < 10; i++)
			bucket_index[i] = 0;

		for (i = 0; i < n; i++)
		{
			rem = (ar[i] / modVal) % 10;
			bucket[rem][bucket_index[rem]] = ar[i];
			bucket_index[rem]++;
		}

		k = 0;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < bucket_index[i]; j++)
			{
				ar[k] = bucket[i][j];
				k++;
			}
			Radix_Print(thisWindow, k);
			sleep(milliseconds(300));
		}
		modVal *= 10;
		
	}
}

int largest(int ar[], int n)
{
	int large = 0, i;
	for (i = 0; i < n; i++)
	{
		if (ar[i] > large)
			large = ar[i];
	}
	return large;
}


void Cocktail_Sort(int ar[], int n, RenderWindow &thisWindow)
{
	int swapped = 1, t;
	int l = 0, u = n - 1;

	while (swapped)
	{
		swapped = 0;
		for (int i = 0; i < u; i++)
			if (ar[i] > ar[i + 1])
			{
				t = ar[i];
				ar[i] = ar[i + 1];
				ar[i + 1] = t;
				swapped = 1;
			}
		Cocktail_Print(thisWindow, l, u);
		sleep(milliseconds(300));
		if (swapped == 0)
			break;
		swapped = 0;
		u--;
		for (int i = u - 1; i >= l; i--)
			if (ar[i] > ar[i + 1])
			{
				t = ar[i];
				ar[i] = ar[i + 1];
				ar[i + 1] = t;
				swapped = 1;
			}
		Cocktail_Print(thisWindow, l, u);
		sleep(milliseconds(300));
		l++;
	}
}

void HeapSort(int arr[], int n, RenderWindow &thisWindow)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		create_heap(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		int t = arr[0];
			arr[0] = arr[i];
			arr[i] = t;
		create_heap(arr, i, 0);
		Heap_Print(thisWindow, i);
		sleep(milliseconds(200));
	}
}

void create_heap(int arr[], int n, int root)
{
	int largest = root;
	int l = 2 * root + 1;
	int r = 2 * root + 2;

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != root)
	{
		int t = arr[largest];
			arr[largest] = arr[root];
			arr[root] = t;
		create_heap(arr, n, largest);
	}
}


//printing functions 

void PrintInit(RenderWindow &newWindow)
{
	int j,i;
	RectangleShape rect;
	RectangleShape button[15];	//there will be total 11 buttons
	Text button_text[15];
	Font font;

	font.loadFromFile("font.ttf");

	//first 7 buttons in one row
	for (i = 0; i < 7; i++)	
	{
		button[i].setFillColor(Color(204, 204, 0, 255));
		button[i].setPosition(10.f + i * 182, 10.f);
		button[i].setSize(Vector2f(width, height));
		button_text[i].setFont(font);
		button_text[i].setCharacterSize(22);
		button_text[i].setFillColor(Color::Black);
	}
	//last 4 buttons in second row
	j = 0;
	for (i = 7; i < 11; i++, j++)
	{
		// last two buttons i.e reset and exit will be treated differently
		if (i == 9 || i == 10)
		{
			button[i].setFillColor(Color(255, 51, 51, 255));
			button[i].setPosition(10.f + j * 182, 60.f);
			button[i].setSize(Vector2f(width, height));
			button_text[i].setFont(font);
			button_text[i].setCharacterSize(22);
			button_text[i].setFillColor(Color::Black);
		}
		else 
		{
			button[i].setFillColor(Color(204, 204, 0, 255));
			button[i].setPosition(10.f + j * 182, 60.f);
			button[i].setSize(Vector2f(width, height));
			button_text[i].setFont(font);
			button_text[i].setCharacterSize(22);
			button_text[i].setFillColor(Color::Black);
		}
		
	}
	

	//button texts and positions
	//found no way to insert them in loop, so just hard coding :-|
	button_text[0].setString("Insertion Sort");
	button_text[0].setPosition(13, 14);

	button_text[1].setString("Bubble Sort");
	button_text[1].setPosition(205, 14);
	
	button_text[2].setString("Selection Sort");
	button_text[2].setPosition(376, 14);

	button_text[3].setString("Shell Sort");
	button_text[3].setPosition(580, 14);

	button_text[4].setString("Merge Sort");
	button_text[4].setPosition(755, 14);

	button_text[5].setString("Quick Sort");
	button_text[5].setPosition(938, 14);

	button_text[6].setString("Radix Sort");
	button_text[6].setPosition(1125, 14);

	button_text[7].setString("Cocktail Sort");
	button_text[7].setPosition(16, 64);

	button_text[8].setString("Heap Sort");
	button_text[8].setPosition(215, 64);

	button_text[9].setString("Reset");
	button_text[9].setPosition(420, 64);

	button_text[10].setString("Exit");
	button_text[10].setPosition(610, 64);


	// button update 

	float mx = Mouse::getPosition(newWindow).x;
	float my = Mouse::getPosition(newWindow).y;


	for (int i = 0; i < 11; i++)
	{
		int hot = mx > button[i].getPosition().x && mx < button[i].getPosition().x + width &&
			my > button[i].getPosition().y && my < button[i].getPosition().y + height;

		if (hot)	//if mouse is hovering over the button
		{
			if(i == 9 || i == 10)
				button[i].setFillColor(Color(255, 140, 102, 255));
			else
				button[i].setFillColor(Color(204, 102, 0, 255));
		}

		//if button is hot and mouse is clicked
		if (hot && Mouse::isButtonPressed(Mouse::Button::Left))
		{
			//all the button funcitons - changing the sortNumber value
			switch (i)
			{
			case 0:
				sortNumber = 1;
				break;
			case 1:
				sortNumber = 2;
				break;
			case 2:
				sortNumber = 3;
				break;
			case 3:
				sortNumber = 4;
				break;
			case 4:
				sortNumber = 5;
				break;
			case 5:
				sortNumber = 6;
				break;
			case 6:
				sortNumber = 7;
				break;
			case 7:
				sortNumber = 8;
				break;
			case 8:
				sortNumber = 9;
				break;

			case 9:
				// reset button
				button[i].setFillColor(Color(255, 0, 0, 255));	// to dark red
				for (i = 0; i < SIZE; i++)
					array[i] = rand() % ArrayLimit;
				sortNumber = 0;
				break;
			
			case 10:
				// exit button
				newWindow.close();
				break;	//no need though
			}
		}
	}

	newWindow.clear();
	// draw initial blocks
	for (j = 0; j < SIZE; j++)
	{
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
	}
	//draw buttons
	for (int i = 0; i < 11; i++)
	{
		newWindow.draw(button[i]);
		button[i].setFillColor(Color::White);
	}
	//draw texts
	for (i = 0; i < 11; i++)
		newWindow.draw(button_text[i]);
	newWindow.display();
}

void Insertion_Print(RenderWindow &newWindow, int i, int t)
{
	int j;
	RectangleShape rect;
			
	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if (j < i)
			rect.setFillColor(Color::Green);
		if(i == SIZE-1)
			rect.setFillColor(Color::Green);
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}

void Bubble_Print(RenderWindow &newWindow, int i)
{
	int j;
	RectangleShape rect;

	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if (j > i)
			rect.setFillColor(Color::Green);
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}

void Selection_Print(RenderWindow &newWindow, int i, int m)
{
	int j;
	RectangleShape rect;

	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if (j < i)
			rect.setFillColor(Color::Green);
		if(j == m)
			rect.setFillColor(Color::Red);
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}

void Shell_Print(RenderWindow &newWindow, int i, int t)
{
	int j;
	RectangleShape rect;

	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if (j == i)
			rect.setFillColor(Color::Green);
		if (array[j] == t)
			rect.setFillColor(Color::Red);
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}

void Merge_Print(RenderWindow &newWindow, int a, int b)
{
	int j;
	RectangleShape rect;

	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if(j >= a and j <= b)
			rect.setFillColor(Color::Red);
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}

void Quick_Print(RenderWindow &newWindow, int a, int b)
{
	int j;
	RectangleShape rect;

	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if (j >= a and j <= b)
			rect.setFillColor(Color::Red);
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}

void Radix_Print(RenderWindow &newWindow, int k)
{
	int j;
	RectangleShape rect;

	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if (j == k)
			rect.setFillColor(Color::Red);
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}

void Cocktail_Print(RenderWindow &newWindow, int l, int u)
{
	int j;
	RectangleShape rect;

	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if (j == l || j == u)
			rect.setFillColor(Color::Red);
		
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}

void Heap_Print(RenderWindow &newWindow, int k)
{
	int j;
	RectangleShape rect;

	newWindow.clear();
	for (j = 0; j < SIZE; j++)
	{
		if (j > k)
			rect.setFillColor(Color::Green);
		if (j == k)
			rect.setFillColor(Color::Red);
		rect.setSize(Vector2f(BlockSize, array[j]));
		rect.setPosition(Gap * j, 760 - array[j]);
		newWindow.draw(rect);
		rect.setFillColor(Color::White);
	}
	newWindow.display();
}