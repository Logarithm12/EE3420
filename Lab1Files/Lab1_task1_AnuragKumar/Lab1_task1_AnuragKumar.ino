/**
 *  \author Anurag Kumar
 *  \file Lab1_task1_AnuragKumar.ino
 *  \brief The program takes 10 words input from the user
 *  	   through the serial port of the arduino, sorts them
 *  	   then prints out the sorted list
 *  \details unless otherwise specified, the functions were
 *  		 written by Anurag Kumar
 */
String words[10];
int i = 0;
String ding = "";


template <typename ding>
void printArray(ding arr[], int size);

void reorderArrays(String arr1[], String arr2[]);

void bubblesort(String arr[], int n);


/**
 *  \brief Setup function, runs once before the loop function
 *  
 */
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start Lab 1 Task 1");
}
/**
 *  \brief Main loop. This function repeats itself continuously in function
 *         execution, and is the main function of the program.
 *  
 *  
 *  \details This function is what takes in the input from the user, and sends
 *  		 that input to the arrays and functions to get it to where it needs
 *  		 to be.
 */
void loop()
{
  //code to handle serial input from user
  Serial.println("Please enter string");
  while (!Serial.available()) {}

  if (Serial.available() > 0) {
    ding = Serial.readStringUntil('\n');
    Serial.print("I got: ");
    Serial.println(ding);
    words[i] = ding;
  }
  Serial.println(ding);
  ++i;
  
  //if there have been 10 strings input, do the sorting then print out
  //the string
  if (i > 9) {
    printArray(words, 10);
    String toSort[10];
    for (int i = 0; i < 10; ++i) {
      toSort[i] = words[i];
      toSort[i].toLowerCase();
    }

    bubblesort(toSort, 10);
    reorderArrays(words, toSort);
    printArray(words, 10);
	
  }
}


/**
 *  \brief prints an array with a passed size
 *  
 *  \param T arr[] The array that is intended to be printed
 *  \param [in] size The size of the array passed to the function
 *  \return returns nothing
 *  
 *  \details This is a template function
 *  
 */
template <typename T>
void printArray(T arr[], int size)
{
  Serial.println("Printing array:");
  for (int i = 0; i < size; ++i)
  {
    Serial.print(arr[i]);
    if (i < size - 1)
      Serial.print(", ");
  }
  Serial.println();
}

/**
 *  \brief This function reorders a string array according to the order that the
 *         second string array passed to it has been ordered in, given that the
 *  	   two arrays hold the same string values, ignoring case, while being ordered
 *  	   differently
 *  
 *  \param String arr1[] the string array to be sorted
 *  \param String arr2[] the sorted string array that is ignoring case
 *  \return The return is the side effect on the first string array passed to the
 * 			function, as it will be sorted after the function executes
 *  
 *  \details This requires both functions to have only 10 elements
 */
void reorderArrays(String arr1[], String arr2[]) {
  int size1 = 10, size2 = 10;
  String finalArr[size1];
  for (int i = 0; i < size1; ++i) {
    for (int j = 0; j < size2; ++j) {
      if (arr1[i].equalsIgnoreCase(arr2[j])) {
        finalArr[j] = arr1[i];
      }
    }
  }
  //deep copy
  for(int i =0;i<10;++i){
    arr1[i] = finalArr[i];
  }
}


/**
 *  \brief Case-sensitive bubble sort for a string array
 *  
 *  \param [in] n the size of the array passed to the function
 *  \return The array passed to the function will be sorted after
 *  		the function finishes executing
 *  
 */
void bubblesort(String arr[], int n) {
  String temp;
  for (int j = 0; j < n - 1; j++)
  {
    for (int i = j + 1; i < n; i++)
    {
      if (arr[j].compareTo(arr[i]) > 0)
      {
        temp =  arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
    }
  }
}
