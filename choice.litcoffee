 PROCESS(coffee_test_process, "Coffee test process");
 AUTOSTART_PROCESSES(&coffee_test_process);
 
 PROCESS_THREAD(coffee_test_process, ev, data)
 {
   PROCESS_BEGIN();
     
   /* step 1 */
   char message[32];
   char buf[100];
     
   strcpy(message,"#1.hello world.");
   strcpy(buf,message);
   printf("step 1: %s\n", buf );
     
   /* End Step 1. We will add more code below this comment later */    
        
   PROCESS_END();
 }
