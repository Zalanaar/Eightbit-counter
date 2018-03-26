#include <systemc.h>


SC_MODULE(eightbit_register_counter) {

	sc_in_clk clock;
	sc_in <bool> reset;
	sc_in <bool> load;
	sc_in <bool> synch_reset;
	sc_out<sc_uint<8> > register_out;


	sc_signal<sc_uint<8> > mycounter;


	void register_store();

	void data_out_method();


	SC_CTOR(eightbit_register_counter) :
		clock("clock"),
		reset("reset"),
		load("load"),
		synch_reset("synch_reset"),
		register_out("register_out")

	{
		cout << "Executing new" << endl;

		SC_CTHREAD(register_store, clock.pos());
		async_reset_signal_is(reset, true);
		SC_METHOD(data_out_method);
		sensitive << mycounter;
	}
};