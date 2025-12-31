#include <stdio.h>
#include "stack.h"
#include "objects.h"
#include "vm.h"

int main(void)
{
    vm_t *vm = create_vm();

    // Creates a frame and pushes it to VM.
    frame_t *frame = get_frame(vm);

    // Creates an object and pushes it to objects stack in the VM.
    object_t *integer = get_int(vm, 3);
    object_t *character = get_char(vm, 'c');
    object_t *real = get_float(vm, 10.3);
    object_t *array = get_array(vm, 4);
    object_t *string = get_string(vm, "my_str");
    object_t *sec_array = get_array(vm, 2);

    // Populate the array.
    set_array(array, 0, integer);
    set_array(array, 1, character);
    set_array(array, 2, string);

    set_array(sec_array, 1, real);
    set_array(sec_array, 2, array);

    // integer is_marked = false at this point.
    printf("==> Just after object creation!\n");
    printf("Integer Marked: %d\n", integer->is_marked);
    printf("Character Marked: %d\n", character->is_marked);
    printf("Array Marked: %d\n", array->is_marked);
    printf("Second Array Marked: %d\n", sec_array->is_marked);
    printf("String Marked: %d\n", string->is_marked);
    printf("Float Marked: %d\n", real->is_marked);

    // Let the frame reference our object.
    frame_reference_obj(frame, sec_array);

    // Now the objects is are unmarked except sec_array.
    printf("\n==> Marking root objects!\n");
    mark(vm);
    printf("Second Array Marked: %d\n", sec_array->is_marked);
    printf("Integer Marked: %d\n", integer->is_marked);
    printf("Character Marked: %d\n", character->is_marked);
    printf("Array Marked: %d\n", array->is_marked);
    printf("String Marked: %d\n", string->is_marked);
    printf("Float Marked: %d\n", real->is_marked);

    printf("\n==> Calling trace to mark child objects!\n");
    trace(vm);
    printf("Integer Marked: %d\n", integer->is_marked);
    printf("Character Marked: %d\n", character->is_marked);
    printf("Array Marked: %d\n", array->is_marked);
    printf("String Marked: %d\n", string->is_marked);
    printf("Float Marked: %d\n", real->is_marked);

    free_vm(vm);
    return 0;
}
