# The	Optimised	Flight	Path	Finder

The	Optimised	Flight	Path	Finder	aims	to	revolutionize	domestic	aviation	route	planning	in	India	
by	creating	an	intelligent	path	optimization	system.	Traditional	light	path	planning	methods	rely	
on	predeined	routes	and	static	optimization	techniques	that	lack	lexibility	and	fail	to	adapt	to	
changing	conditions.	This	application	will	calculate	optimal	light	paths	between	domestic	
airports	in	India	primarily	based	on	distance,	helping	to	minimize	fuel	consumption,	reduce	
travel	times,	and	enhance	overall	operational	ef iciency.	The	user-friendly	C++	GUI	application	
makes	advanced	path-inding	algorithms	accessible	through	an	intuitive	graphical	interface,	
illing	the	gap	between	expensive	commercial	light	planning	software	and	the	needs	of	domestic	
carriers.	The	project	will	help	promote	both	economic	and	environmental	beneits	for	India's	
aviation	industry	through	more	ef icient	route	planning.

Project Approach and Architecture:
 
![image](https://github.com/user-attachments/assets/1e717662-e230-4593-80b0-15f6fa9fec24)

The tasks that are completed:

![image](https://github.com/user-attachments/assets/8070afa6-1cc0-472e-89f2-62a5d7817c09)

Challenges

 • A primary challenge has been the acquisition of accurate and comprehensive data for Indian airports. 
Finding reliable sources with complete geographical coordinates, airport codes, and other relevant 
information proved difficult. Available datasets were often incomplete, outdated, or contained 
inconsistencies. This challenge required extensive research across multiple sources, cross-referencing 
information, and manual verification to create a unified and accurate database of Indian airports with 
precise coordinates. 

• The implementation of a graphical user interface (GUI) in C++ has presented significant technical 
challenges. While C++ excels at performance-critical backend operations, GUI development in the 
language is considerably more complex than in other programming environments. Working with Qt 
framework requires steep learning curves, managing memory properly, and handling complex event 
systems. The team has had to allocate additional time for UI development and consider simplifying 
certain interface elements to ensure timely delivery without compromising functionality.

Future Scope

• Algorithmic Diversification: Future enhancements could involve implementing and evaluating the 
project using alternative pathfinding algorithms, such as Bellman-Ford or Floyd-Warshall, to compare 
their performance and suitability for various scenarios. 
•Global Route Expansion: The system's capabilities can be expanded beyond domestic routes to in
clude international destinations, requiring the integration of a broader airport dataset and adherence to 
international aviation standards. 
•Multi-Factor Optimization: While currently focused on distance, the project can evolve to optimize 
flight paths based on a comprehensive set of factors, including fuel consumption, flight time, opera
tional cost, real-time airspace restrictions, and environmental considerations. 
•Rigorous Real-World Validation: Comprehensive testing and validation using real-world flight data 
and operational scenarios would further ensure the system's robustness and accuracy in practical ap
plication.

Project Outcomes
 The key deliverables of the project include: 
1.A fully functional C++ GUI application with an intuitive user interface for selecting origin and 
destination airports in India  
2.A backend system implementing graph-based optimization algorithms (Dijkstra's and A*) for 
finding the most efficient routes  
3.Visual representation of optimal flight paths on a map of India with relevant information display 
(distance, route details)  
4.A comprehensive dataset of Indian airports with verified geographical coordinates  
5.Technical documentation covering the system architecture, algorithm implementations, and 
code structure  
6.User guide explaining how to effectively use the application for flight path planning  
7. Final project report documenting methodologies, challenges encountered, and recommendations 
for future enhancement

Progress Overview

 •The foundational components including data acquisition, graph representation, and algorithm 
implementation are fully complete and tested. Both Dijkstra's algorithm and A* have been 
successfully implemented and optimized for the airport network. All backend systems, including the 
path optimization algorithms and data structures, are functioning as expected with excellent 
performance results on the complete dataset of Indian airports. 
•The fundamental structure and essential features of the user interface are now in place. The team has 
successfully completed the integration of visual elements and refined the styling.  
•Despite the complexities inherent in C++ GUI development, the team is on schedule to deliver the 
complete application by the deadline, with all planned functionalities fully operational

Deliverable Program

• Airport dataset: 100% complete - A comprehensive dataset of Indian airports has been acquired 
and preprocessed. 
• Graph representation: 100% complete - The adjacency list structure is fully implemented and 
integrated with the airport data.   
• Dijkstra's algorithm: 100% complete - Implementation is fully optimized and tested for the 
complete dataset.  
• UI for airport selection: 70% complete - Basic functionality working, styling and user 
experience improvements needed.
• A* algorithm: 100% complete - Implementation is fully optimized and tested as an alternative 
path-finding solution.  
• Backend system integration: 100% complete - All backend components work together 
seamlessly.  
