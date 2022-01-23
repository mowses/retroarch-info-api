import fs from 'fs';
import net from 'net';

const Client = function(options)
{
	if (!options.unixfile) throw 'Please specify a file path.';

	this.getUnixFile = function ()
	{
		return options.unixfile;
	}

	this.ask = function (what, callback)
	{
		if (this.sock.destroyed) return this;

		requests.push([what, callback]);

		if (requests.length === 1) {
			write(what);
		}

		return this;
	}

	this.close = function ()
	{
		this.sock.destroy();

		return this;
	}

	/**
	 * Available events: (possible more: https://nodejs.org/api/net.html#event-close_1)
	 * connect
	 * ready
	 * data
	 * close
	 * 
	 * Usage ex: sock.on('connect', function(){...})
	 */
	this.on = function (...on)
	{
		this.sock.on(...on);

		return this;
	}

	function write(what)
	{
		let buffer = Buffer.isBuffer(what) ? what : Buffer.from(what);
		this.sock.write(Buffer.concat([buffer, Buffer.from("\n")]));
	}

	function init()
	{
		this.sock = net.createConnection({
			path: options.unixfile,
		});

		this.on('data', function(response) {
			let response_message = response.toString();

			if (requests.length === 0) {
				console.log(response_message);
				return;
			}

			const [what, callback] = requests[0];
			
			if (response_message.indexOf(what + ':') !== 0) {
				console.log(response_message);
				return;
			}

			requests.shift();
			callback(response_message.substr(what.length + 1));
			
			if (requests.length > 0) {
				write(requests[0][0]);
			}

		});
	}

	var requests = [];
	var write = write.bind(this);
	var init = init.bind(this);

	init();
}

export default Client;