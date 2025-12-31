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
    set_array(array, 3, sec_array);

    set_array(sec_array, 1, real);
    set_array(sec_array, 2, array);

    // Let the frame reference our object.
    frame_reference_obj(frame, sec_array);

    // GC call.
    // mark() -> trace() -> sweep();
    run_gc(vm);

    free_vm(vm);
    return 0;
}
