/*********************************************************************************************************************
* File Information:
* Author : Alsayed Alsisi
* Date   : Wednesday, July 14, 2024
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* File Name: array_test.c
* File Description: This file contains the implementation of the different tests for the CustomArray component.
* License:
*********************************************************************************************************************/


/*********************************************************************************************************************
                                         << File Inclusions >>
*********************************************************************************************************************/
#include <stdio.h>
#include "array_test.h"
#include "CustomArray.h"
#define ARRAY_CAPACITY   20

/*********************************************************************************************************************
                                  << Private Datatypes >>
*********************************************************************************************************************/
typedef enum
{
    TEST_PASSED = 0,
    TEST_FAILED

}test_result_t;

/*********************************************************************************************************************
                                  << Private Variable Declarations >>
*********************************************************************************************************************/
static custarr_t my_array;
static FILE *fptr; /** pointer to the file that will be used for logging test results **/
/*********************************************************************************************************************
                                  << Private Function Declarations >>
*********************************************************************************************************************/
/** Test Functions **/
static void initArray_test(void);
static void freeArray_test(void);
static void getElement_atEnd_test(void);
static void insertElement_atIndex_test(void);
static void deleteElement_atIndex_test(void);
static void getElement_atIndex_test(void);
/*********************************************************************************************************************
                                  << Public Function Definitions >>
*********************************************************************************************************************/
void test_run(void)
{


  fptr = fopen("test_reults.txt", "w");
  fprintf(fptr, "Test Results: ");


  initArray_test();
  freeArray_test();
  getElement_atEnd_test();
  deleteElement_atIndex_test();
  insertElement_atIndex_test();
  getElement_atIndex_test();

   fclose(fptr);

}







static void initArray_test(void)
{
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;
    test_result_t test1_result = TEST_FAILED;
    test_result_t test2_result = TEST_FAILED;


    /** Test1: init array for the first time **/
    ret_val = initArray(&my_array, ARRAY_CAPACITY);
    if(CUSTARR_OP_SUCCESS == ret_val)
    {
        test1_result = TEST_PASSED;
    }



    /** Test2: init array for the second time **/
    ret_val = initArray(&my_array, ARRAY_CAPACITY);
    if(CUSTARR_OP_FAIL== ret_val)
    {
        test2_result = TEST_PASSED;
    }
    /** Print test results**/
    if((TEST_PASSED == test1_result) && (TEST_PASSED == test2_result))
    {
        fprintf(fptr, "\ninitArray_test() test passed.");
    }
    else
    {
        fprintf(fptr, "\ninitArray_test() test failed.");
    }

}
static void getElement_atEnd_test(void)
{

    int data = 0;



    test_result_t test1_result = TEST_FAILED;
    test_result_t test2_result = TEST_FAILED;


    /** Test1: insert 1 element and read the last element  **/
    insertElement_atEnd(&my_array, 100);
    getElement_atEnd(&my_array, &data);
    if(100 == data)
    {
        test1_result = TEST_PASSED;
    }


    /** Test2: insert 3 elements and read the last element  **/
    insertElement_atEnd(&my_array, 100);
    insertElement_atEnd(&my_array, 200);
    insertElement_atEnd(&my_array, 300);
    getElement_atEnd(&my_array, &data);
    if(300 == data)
    {
        test2_result = TEST_PASSED;
    }

    /** Print test results**/
    if((TEST_PASSED == test1_result) && (TEST_PASSED == test2_result))
    {
        fprintf(fptr, "\ngetElement_atEnd_test() test passed.");
    }
    else
    {
        fprintf(fptr, "\ngetElement_atEnd_test() test failed.");
    }






}

static void freeArray_test(void)
{
    test_result_t test1_result = TEST_FAILED;
    test_result_t test2_result = TEST_FAILED;
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;


    /** Test1: Check for freearray behavior before creating any nodes(array is empty)  **/
    ret_val = freeArray(&my_array);

    if(CUSTARR_OP_FAIL == ret_val)
    {
        test1_result = TEST_PASSED;
    }


    /** Test2: Check for init after creating nodes  **/
    /** Step1: Insert an element **/
    ret_val = insertElement_atEnd(&my_array, 100);

    /** Step2: free array again **/
    ret_val = freeArray(&my_array);

    if(CUSTARR_OP_SUCCESS == ret_val)
    {
        test2_result = TEST_PASSED;
    }

    /** Print test results**/
    if((TEST_PASSED == test1_result) && (TEST_PASSED == test2_result))
    {
        fprintf(fptr, "\nfreeArray_test() test passed.");
    }
    else
    {
        fprintf(fptr, "\nfreeArray_test() test failed.");
    }


}

static void insertElement_atIndex_test(void)
{
    test_result_t test1_result = TEST_FAILED;
    test_result_t test2_result = TEST_FAILED;
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;

    freeArray(&my_array);

    /** Test1: insert element with an index outside the available range **/
    ret_val = insertElement_atIndex(&my_array, 30, 99);
    if(CUSTARR_OP_OUTOFRANGE == ret_val)
    {
        test1_result = TEST_PASSED;
    }


    /** Test2: insert element with an index within the available range  **/
    insertElement_atEnd(&my_array, 100);
    insertElement_atEnd(&my_array, 100);
    ret_val = insertElement_atIndex(&my_array, 1, 99);

    if(CUSTARR_OP_SUCCESS == ret_val)
    {
        test2_result = TEST_PASSED;
    }

    /** Print test results **/
    if((TEST_PASSED == test1_result) && (TEST_PASSED == test2_result))
    {
        fprintf(fptr, "\ninsertElement_atIndex() test passed.");
    }
    else
    {
        fprintf(fptr, "\ninsertElement_atIndex() test failed.");
    }
}


static void deleteElement_atIndex_test(void)
{
    test_result_t test1_result = TEST_FAILED;
    test_result_t test2_result = TEST_FAILED;
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;

    freeArray(&my_array);

    /** Test1: Delete element with an index outside the available range **/
    ret_val = deleteElement_atIndex(&my_array, 1);
    if(CUSTARR_OP_OUTOFRANGE == ret_val)
    {
        test1_result = TEST_PASSED;
    }


    /** Test2: Delete element with an index within the available range  **/
    /** Step1: Insert an element **/
    ret_val = insertElement_atEnd(&my_array, 100);

    /** Step2: delete the inserted element and check op error code**/
    ret_val = deleteElement_atIndex(&my_array, 1);


    if(CUSTARR_OP_SUCCESS == ret_val)
    {
        test2_result = TEST_PASSED;
    }

    /** Print test results**/
    if((TEST_PASSED == test1_result) && (TEST_PASSED == test2_result))
    {
        fprintf(fptr, "\ndeleteElement_atIndex() test passed.");
    }
    else
    {
        fprintf(fptr, "\ndeleteElement_atIndex() test failed.");
    }

}

static void getElement_atIndex_test(void)
{
    test_result_t test1_result = TEST_FAILED;
    test_result_t test2_result = TEST_FAILED;
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;
    int data;

    freeArray(&my_array);

    /** Test1: read element with an index outside the available range **/
    ret_val = getElement_atIndex(&my_array, 30,&data);
    if(CUSTARR_OP_OUTOFRANGE == ret_val)
    {
        test1_result = TEST_PASSED;
    }


    /** Test2: insert element with an index within the available range  **/
    insertElement_atEnd(&my_array, 100);
    insertElement_atEnd(&my_array, 100);
    ret_val = getElement_atIndex(&my_array, 1,&data);

    if(CUSTARR_OP_SUCCESS == ret_val)
    {
        test2_result = TEST_PASSED;
    }

    /** Print test results **/
    if((TEST_PASSED == test1_result) && (TEST_PASSED == test2_result))
    {
        fprintf(fptr, "\ngetElement_atIndex() test passed.");
    }
    else
    {
        fprintf(fptr, "\ngetElement_atIndex() test failed.");
    }
}
