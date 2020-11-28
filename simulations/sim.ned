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

package tsch.simulations;

import tsch.ACM;
import tsch.Node;

network sim
{
    @display("bgb=800,423");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 4ms;
        }

    submodules:
        acm: ACM;
        n[10]: Node;
    connections:
        n[1].out++ --> Channel --> n[0].in++;
        n[1].in++ <-- Channel <-- n[0].out++;

        n[2].out++ --> Channel --> n[0].in++;
        n[2].in++ <-- Channel <-- n[0].out++;

        n[3].out++ --> Channel --> n[1].in++;
        n[3].in++ <-- Channel <-- n[1].out++;

        n[4].out++ --> Channel --> n[0].in++;
        n[4].in++ <-- Channel <-- n[0].out++;

        n[5].out++ --> Channel --> n[0].in++;
        n[5].in++ <-- Channel <-- n[0].out++;

        n[6].out++ --> Channel --> n[5].in++;
        n[6].in++ <-- Channel <-- n[5].out++;

        n[7].out++ --> Channel --> n[2].in++;
        n[7].in++ <-- Channel <-- n[2].out++;

        n[8].out++ --> Channel --> n[1].in++;
        n[8].in++ <-- Channel <-- n[1].out++;

        n[9].out++ --> Channel --> n[5].in++;
        n[9].in++ <-- Channel <-- n[5].out++;

}
