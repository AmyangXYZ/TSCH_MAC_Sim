//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package tsch;

module Node
{
    parameters:
        @display("bgb=503,380;i=misc/node2");
        bool isRoot = default(false);
        int parent = default(-1);
    gates:
        input in[];
        output out[];

    submodules:

        source: Source {
            parameters:
                @display("p=401,269");
            gates:
                out;
        }

        sink: Sink {
            parameters:
                @display("p=78,269");
            gates:
                in;
        }

        rxm: RXM {
            parameters:

                @display("p=78,73");
            gates:
                in[sizeof(in)];
        }

        txm: TXM {
            parameters:

                @display("p=401,73");
            gates:
                in[2];
                out[sizeof(out)];
        }

    connections:
        for i=0..sizeof(in)-1 {
            in[i] --> rxm.in[i];
        }

        rxm.out[0] --> sink.in;

        source.out --> txm.in++;

        rxm.out[1] --> txm.in++;

        for j=0..sizeof(out)-1 {
            txm.out[j] --> out[j];
        }

}
