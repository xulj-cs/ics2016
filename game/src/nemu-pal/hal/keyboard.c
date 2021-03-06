#include "hal.h"

#define NR_KEYS 18

enum {KEY_STATE_EMPTY, KEY_STATE_WAIT_RELEASE, KEY_STATE_RELEASE, KEY_STATE_PRESS};

/* Only the following keys are used in NEMU-PAL. */
static const int keycode_array[] = {
	K_UP, K_DOWN, K_LEFT, K_RIGHT, K_ESCAPE,
	K_RETURN, K_SPACE, K_PAGEUP, K_PAGEDOWN, K_r,
	K_a, K_d, K_e, K_w, K_q,
	K_s, K_f, K_p
};

static int key_state[NR_KEYS]={0};

//volatile static int scan_code = -1;
static inline int
get_index(int keycode) {
	assert(keycode >= 0 && keycode < 0x80);
	int i;
	for(i=0; i<NR_KEYS; i++){
		if(keycode_array[i] == keycode)
			return i;
	}
	//assert(0);
	return -1;
}
static inline int
get_keycode(int index) {
	assert(index >= 0 && index < NR_KEYS);
	return keycode_array[index];
}
/*
static inline int
query_key(int index) {
	assert(index >= 0 && index < NR_KEYS);
	return key_state[index];
}
*/
static inline void
release_key(int index) {
	assert(index >= 0 && index < NR_KEYS);
	switch(key_state[index]){
		case KEY_STATE_WAIT_RELEASE: key_state[index] = KEY_STATE_RELEASE;
//									Log("release %x,waiting the slove",index);
								    break;
//		default:assert(0);
	}
	//key_state[index] = KEY_STATE_WAIT_RELEASE;
}

static inline void
press_key(int index) {
	assert(index >= 0 && index < NR_KEYS);
	switch(key_state[index]){
		case KEY_STATE_EMPTY: key_state[index] = KEY_STATE_PRESS; 
//							Log("press %x,waiting the slove",index);
							  break;
		case KEY_STATE_WAIT_RELEASE:  
//							Log("wait release");
							break;
//		default:assert(0);
	}
}
/*
static inline void
clear_key(int index) {
	assert(index >= 0 && index < NR_KEYS);
	key_state[index] = KEY_STATE_EMPTY;
}
*/
void
keyboard_event(void) {
	/* TODO: Fetch the scancode and update the key states. */
	int scan_code = in_byte(0x60);
//	Log("%x",scan_code);
	//if(temp!=scan_code){
	//	scan_code = temp;
		if(scan_code > 0x80){
			int index = get_index(scan_code-0x80);
			if(index!=-1)
				release_key(index);
		}
		else{
			int index = get_index(scan_code);
			if(index!=-1)
				press_key(index);
		}
	//}
	//assert(0);
}

bool 
process_keys(void (*key_press_callback)(int), void (*key_release_callback)(int)) {
	cli();
	/* TODO: Traverse the key states. Find a key just pressed or released.
	 * If a pressed key is found, call `key_press_callback' with the keycode.
	 * If a released key is found, call `key_release_callback' with the keycode.
	 * If any such key is found, the function return true.
	 * If no such key is found, the function return false.
	 * Remember to enable interrupts before returning from the function.
	 */
	int i;
	bool flag = false;
	for(i=0; i<NR_KEYS; i++){
		if(key_state[i] == KEY_STATE_PRESS){
		
			key_state[i] = KEY_STATE_WAIT_RELEASE;
			key_press_callback( get_keycode(i) );
//			Log("just press %x",i);
			flag = true;
			//sti();
			//return true;

		}
		if(key_state[i] == KEY_STATE_RELEASE){
		
			key_state[i] = KEY_STATE_EMPTY;
			key_release_callback( get_keycode(i) );
//			Log("just release %x",i);
			flag = true;
			//sti();
			//return true;

		}
	}
	//assert(0);
	sti();
	if( flag )
		return true;
	else
//		Log("nothing happens");
		return false;
}
