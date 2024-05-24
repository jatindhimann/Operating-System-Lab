<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Operating System Algorithms</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
        }
        h1, h2, h3 {
            color: #333;
        }
        ul {
            list-style: none;
            padding: 0;
        }
        ul li {
            margin: 5px 0;
        }
        a {
            color: #007BFF;
            text-decoration: none;
        }
        a:hover {
            text-decoration: underline;
        }
    </style>
</head>
<body>
    <h1>Operating System Algorithms</h1>
    <p>This project implements a variety of operating system algorithms, covering CPU scheduling, deadlock detection, page replacement, disk scheduling, and memory management. Each category provides several algorithm choices for user selection through a simple menu-driven interface.</p>

    <h2>Table of Contents</h2>
    <ul>
        <li><a href="#cpu-scheduling-algorithms">CPU Scheduling Algorithms</a></li>
        <li><a href="#deadlock-algorithms">Deadlock Algorithms</a></li>
        <li><a href="#page-replacement-algorithms">Page Replacement Algorithms</a></li>
        <li><a href="#disk-scheduling-algorithms">Disk Scheduling Algorithms</a></li>
        <li><a href="#memory-management-algorithms">Memory Management Algorithms</a></li>
        <li><a href="#getting-started">Getting Started</a></li>
        <li><a href="#usage">Usage</a></li>
        <li><a href="#contributing">Contributing</a></li>
        <li><a href="#license">License</a></li>
    </ul>

    <h2 id="cpu-scheduling-algorithms">CPU Scheduling Algorithms</h2>
    <p>This module supports the following CPU scheduling algorithms:</p>
    <ul>
        <li><strong>First Come First Serve (FCFS)</strong></li>
        <li><strong>Shortest Job First (SJF)</strong>
            <ul>
                <li>Preemptive</li>
                <li>Non-Preemptive</li>
            </ul>
        </li>
        <li><strong>Priority Scheduling</strong>
            <ul>
                <li>Preemptive</li>
                <li>Non-Preemptive</li>
            </ul>
        </li>
        <li><strong>Round Robin</strong></li>
    </ul>

    <h2 id="deadlock-algorithms">Deadlock Algorithms</h2>
    <p>This module includes:</p>
    <ul>
        <li><strong>Banker's Algorithm</strong>
            <ul>
                <li>Safety Algorithm</li>
                <li>Request and Resource Allocation</li>
            </ul>
        </li>
    </ul>

    <h2 id="page-replacement-algorithms">Page Replacement Algorithms</h2>
    <p>The page replacement module supports:</p>
    <ul>
        <li><strong>First In First Out (FIFO)</strong></li>
        <li><strong>Optimal Page Replacement</strong></li>
        <li><strong>Least Recently Used (LRU)</strong></li>
        <li><strong>Most Frequently Used (MFU)</strong></li>
        <li><strong>Least Frequently Used (LFU)</strong></li>
    </ul>

    <h2 id="disk-scheduling-algorithms">Disk Scheduling Algorithms</h2>
    <p>The disk scheduling module supports:</p>
    <ul>
        <li><strong>First Come First Serve (FCFS)</strong></li>
        <li><strong>Shortest Seek Time First (SSTF)</strong></li>
        <li><strong>SCAN</strong></li>
        <li><strong>C-SCAN</strong></li>
        <li><strong>LOOK</strong></li>
        <li><strong>C-LOOK</strong></li>
    </ul>

    <h2 id="memory-management-algorithms">Memory Management Algorithms</h2>
    <p>The memory management module includes:</p>
    <ul>
        <li><strong>First Fit</strong></li>
        <li><strong>Best Fit</strong></li>
        <li><strong>Worst Fit</strong></li>
    </ul>

    <h2 id="getting-started">Getting Started</h2>
    <h3>Prerequisites</h3>
    <p>To compile and run this project, you need:</p>
    <ul>
        <li>A C++ compiler (GCC, Clang, MSVC, etc.)</li>
        <li>Standard Template Library (STL) support</li>
    </ul>

    <h3>Installation</h3>
    <ol>
        <li>Clone the repository:
            <pre><code>git clone https://github.com/yourusername/operating-system-algorithms.git
cd operating-system-algorithms</code></pre>
        </li>
        <li>Build the project:
            <pre><code>g++ -o os_algorithms main.cpp CPU_Scheduling_algorithms/*.cpp Page_Replacement_algorithms/*.cpp Memory_Management/*.cpp Disk_Scheduling/*.cpp Deadlocks/*.cpp</code></pre>
        </li>
    </ol>

    <h2 id="usage">Usage</h2>
    <p>Run the compiled executable:</p>
    <pre><code>./os_algorithms</code></pre>
    <p>Follow the on-screen menu to select the desired algorithm and input the necessary parameters.</p>

    <h3>Example</h3>
    <ol>
        <li>Select CPU Scheduling Algorithms:
            <pre><code>1. CPU Scheduling Algorithms</code></pre>
        </li>
        <li>Choose a specific scheduling algorithm, such as FCFS:
            <pre><code>1. First Come First Serve (FCFS)</code></pre>
        </li>
    </ol>
    <p>The program will then prompt you to enter the required data and display the results.</p>

    <h2 id="contributing">Contributing</h2>
    <p>Contributions are welcome! Please fork the repository and use a feature branch. Pull requests are warmly welcome.</p>
    <ol>
        <li>Fork the repository</li>
        <li>Create your feature branch (<code>git checkout -b feature/AmazingFeature</code>)</li>
        <li>Commit your changes (<code>git commit -m 'Add some AmazingFeature'</code>)</li>
        <li>Push to the branch (<code>git push origin feature/AmazingFeature</code>)</li>
        <li>Create a new Pull Request</li>
    </ol>

    <h2 id="license">License</h2>
    <p>This project is licensed under the MIT License. See the <code>LICENSE</code> file for details.</p>

    <hr>
    <p>This README provides an overview of the project and instructions on how to get started and contribute. The project structure and the algorithm implementations are organized to facilitate easy use and extension. Happy coding!</p>
</body>
</html>
