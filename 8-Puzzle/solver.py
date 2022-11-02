import math
import sys
import puzz
import pdqpq


GOAL_STATE = puzz.EightPuzzleBoard("012345678")


def solve_puzzle(start_state, flavor):
    """Perform a search to find a solution to a puzzle.
    
    Args:
        start_state (EightPuzzleBoard): the start state for the search
        flavor (str): tag that indicate which type of search to run.  Can be one of the following:
            'bfs' - breadth-first search
            'ucost' - uniform-cost search
            'greedy-h1' - Greedy best-first search using a misplaced tile count heuristic
            'greedy-h2' - Greedy best-first search using a Manhattan distance heuristic
            'greedy-h3' - Greedy best-first search using a weighted Manhattan distance heuristic
            'astar-h1' - A* search using a misplaced tile count heuristic
            'astar-h2' - A* search using a Manhattan distance heuristic
            'astar-h3' - A* search using a weighted Manhattan distance heuristic
    
    Returns: 
        A dictionary containing describing the search performed, containing the following entries:
        'path' - list of 2-tuples representing the path from the start to the goal state (both 
            included).  Each entry is a (str, EightPuzzleBoard) pair indicating the move and 
            resulting successor state for each action.  Omitted if the search fails.
        'path_cost' - the total cost of the path, taking into account the costs associated with 
            each state transition.  Omitted if the search fails.
        'frontier_count' - the number of unique states added to the search frontier at any point 
            during the search.
        'expanded_count' - the number of unique states removed from the frontier and expanded 
            (successors generated)

    """
    if flavor.find('-') > -1:
        strat, heur = flavor.split('-')
    else:
        strat, heur = flavor, None
    if strat == 'bfs':
        return BreadthFirstSolver().solve(start_state)
    elif strat == 'ucost':
        return Uniform_Cost_Search().solve(start_state)
    elif strat == 'greedy':
        if heur == "h1":
            return Greedy_Best_First().solve_greedy_h1(start_state)
        elif heur == "h2":
            return Greedy_Best_First().solve_greedy_h2(start_state)
        elif heur == "h3":
            return Greedy_Best_First().solve_greedy_h3(start_state)
    elif strat == 'astar':
        if heur == "h1":
            return A_Star().solve_astar_h1(start_state)
        elif heur == "h2":
            return A_Star().solve_astar_h2(start_state)
        elif heur == "h3":
            return A_Star().solve_astar_h3(start_state)
    else:
        raise ValueError("Unknown search flavor '{}'".format(flavor))

class BreadthFirstSolver:
    """Implementation of Breadth-First Search based puzzle solver"""

    def __init__(self):
        self.goal = GOAL_STATE
        self.parents = {}  # state -> parent_state
        self.frontier = pdqpq.FifoQueue()
        self.explored = set()
        self.frontier_count = 0  # increment when we add something to frontier
        self.expanded_count = 0  # increment when we pull something off frontier and expand
    
    def solve(self, start_state):
        """Carry out the search for a solution path to the goal state.
        
        Args:
            start_state (EightPuzzleBoard): start state for the search 
        
        Returns:
            A dictionary describing the search from the start state to the goal state.

        """
        self.parents[start_state] = None
        self.add_to_frontier(start_state)

        if start_state == self.goal:  # edge case        
            return self.get_results_dict(start_state)

        while not self.frontier.is_empty():
            node = self.frontier.pop()  # get the next node in the frontier queue
            succs = self.expand_node(node)

            for move, succ in succs.items():
                if (succ not in self.frontier) and (succ not in self.explored):
                    self.parents[succ] = node

                    # BFS checks for goal state _before_ adding to frontier
                    if succ == self.goal:
                        return self.get_results_dict(succ)
                    else:
                        self.add_to_frontier(succ)

        # if we get here, the search failed
        return self.get_results_dict(None) 

    def add_to_frontier(self, node):
        """Add state to frontier and increase the frontier count."""
        self.frontier.add(node)
        self.frontier_count += 1

    def expand_node(self, node):
        """Get the next state from the frontier and increase the expanded count."""
        self.explored.add(node)
        self.expanded_count += 1
        return node.successors()

    def get_results_dict(self, state):
        """Construct the output dictionary for solve_puzzle()
        
        Args:
            state (EightPuzzleBoard): final state in the search tree
        
        Returns:
            A dictionary describing the search performed (see solve_puzzle())

        """
        results = {}
        results['frontier_count'] = self.frontier_count
        results['expanded_count'] = self.expanded_count
        if state:
            results['path_cost'] = self.get_cost(state)
            path = self.get_path(state)
            moves = ['start'] + [ path[i-1].get_move(path[i]) for i in range(1, len(path)) ]
            results['path'] = list(zip(moves, path))
        return results

    def get_path(self, state):
        """Return the solution path from the start state of the search to a target.
        
        Results are obtained by retracing the path backwards through the parent tree to the start
        state for the serach at the root.
        
        Args:
            state (EightPuzzleBoard): target state in the search tree
        
        Returns:
            A list of EightPuzzleBoard objects representing the path from the start state to the
            target state

        """
        path = []
        while state is not None:
            path.append(state)
            state = self.parents[state]
        path.reverse()
        return path

    def get_cost(self, state): 
        """Calculate the path cost from start state to a target state.
        
        Transition costs between states are equal to the square of the number on the tile that 
        was moved. 

        Args:
            state (EightPuzzleBoard): target state in the search tree
        
        Returns:
            Integer indicating the cost of the solution path

        """
        cost = 0
        path = self.get_path(state)
        for i in range(1, len(path)):
            x, y = path[i-1].find(None)  # the most recently moved tile leaves the blank behind
            tile = path[i].get_tile(x, y)        
            cost += int(tile)**2
        return cost

class Uniform_Cost_Search(BreadthFirstSolver):

    def __init__(self):
        self.goal = GOAL_STATE
        self.parents = {}  # state -> parent_state
        self.frontier = pdqpq.PriorityQueue()
        self.explored = set()
        self.frontier_count = 0  # increment when we add something to frontier
        self.expanded_count = 0  # increment when we pull something off frontier and expand
    
    def solve(self, start_state):
        self.parents[start_state] = None
        self.add_to_frontier_ucost(start_state)

        if start_state == self.goal:    
            return self.get_results_dict(start_state)

        while not self.frontier.is_empty():
            node = self.frontier.pop()

            if self.goal == node:
                return self.get_results_dict(node)

            successors = self.expand_node(node)

            for move, successor in successors.items():

                if (successor not in self.frontier) and (successor not in self.explored):
                    self.parents[successor] = node
                    self.add_to_frontier_ucost(successor)
                elif (successor in self.frontier):
                    holder = self.parents[successor]
                    self.parents[successor] = node
                    if self.frontier.get(successor) > self.get_cost(successor):
                        self.frontier_update_ucost(successor)
                    else:
                        self.parents[successor] = holder

        return self.get_results_dict(None)

    def frontier_update_ucost(self, node):
        self.frontier.add(node, self.get_cost(node))

    def add_to_frontier_ucost(self, node):
        """Add state to frontier and increase the frontier count."""
        self.frontier.add(node, self.get_cost(node))
        self.frontier_count += 1

class Greedy_Best_First(Uniform_Cost_Search):
    def __init__(self):
        self.goal = GOAL_STATE
        self.parents = {}  # state -> parent_state
        self.frontier = pdqpq.PriorityQueue()
        self.explored = set()
        self.frontier_count = 0  # increment when we add something to frontier
        self.expanded_count = 0  # increment when we pull something off frontier and expand
    
    def solve_greedy_h1(self, start_state):
        self.parents[start_state] = None
        self.add_to_frontier_h1(start_state)

        if start_state == self.goal:    
            return self.get_results_dict(start_state)

        while not self.frontier.is_empty():
            node = self.frontier.pop()
            successors = self.expand_node(node)
            
            if node ==self.goal:
                return self.get_results_dict(node)
            
            for move, successor in successors.items():
                if (successor not in self.frontier) and (successor not in self.explored):
                   self.parents[successor] = node
                   self.add_to_frontier_h1(successor)

            #         if successor == self.goal:
            #             return self.get_results_dict(successor)
            #         else:
            #             self.add_to_frontier_h1(successor)

        return self.get_results_dict(None)
    
    def h1_cost(self, node):
        sum = 0

        if (node.find("1") != (1,2)):
            sum += 1
        if (node.find("2") != (2,2)):
            sum += 1
        if (node.find("3") != (0,1)):
            sum += 1
        if (node.find("4") != (1,1)):
            sum += 1
        if (node.find("5") != (2,1)):
            sum += 1
        if (node.find("6") != (0,0)):
            sum += 1
        if (node.find("7") != (1,0)):
            sum += 1
        if (node.find("8") != (2,0)):
            sum += 1

        return sum

    def add_to_frontier_h1(self, node):
        """Add state to frontier and increase the frontier count."""
        self.frontier.add(node, self.h1_cost(node))
        self.frontier_count += 1

    def solve_greedy_h2(self, start_state):
        self.parents[start_state] = None
        self.add_to_frontier_h2(start_state)

        if start_state == self.goal:    
            return self.get_results_dict(start_state)

        while not self.frontier.is_empty():
            node = self.frontier.pop()
            successors = self.expand_node(node)
            
            if node ==self.goal:
                return self.get_results_dict(node)
            
            for move, successor in successors.items():
                if (successor not in self.frontier) and (successor not in self.explored):
                   self.parents[successor] = node
                   self.add_to_frontier_h2(successor)
                   
        return self.get_results_dict(None)

    def h2_cost(self, node):
        
        t1 = node.find("1")
        t2 = node.find("2")
        t3 = node.find("3")
        t4 = node.find("4")
        t5 = node.find("5")
        t6 = node.find("6")
        t7 = node.find("7")
        t8 = node.find("8")

        sum_t1 = abs(t1[0] - 1) + abs(t1[1] - 2)
        sum_t2 = abs(t2[0] - 2) + abs(t2[1] - 2)
        sum_t3 = abs(t3[0] - 0) + abs(t3[1] - 1)
        sum_t4 = abs(t4[0] - 1) + abs(t4[1] - 1)
        sum_t5 = abs(t5[0] - 2) + abs(t5[1] - 1)
        sum_t6 = abs(t6[0] - 0) + abs(t6[1] - 0)
        sum_t7 = abs(t7[0] - 1) + abs(t7[1] - 0)
        sum_t8 = abs(t8[0] - 2) + abs(t8[1] - 0)

        sum_final = sum_t1 + sum_t2 + sum_t3 + sum_t4 + sum_t5 + sum_t6 + sum_t7 + sum_t8

        return sum_final

    def add_to_frontier_h2(self, node):
        """Add state to frontier and increase the frontier count."""
        self.frontier.add(node, self.h2_cost(node))
        self.frontier_count += 1

    def solve_greedy_h3(self, start_state):
        self.parents[start_state] = None
        self.add_to_frontier_h3(start_state)

        if start_state == self.goal:    
            return self.get_results_dict(start_state)

        while not self.frontier.is_empty():
            node = self.frontier.pop()
            successors = self.expand_node(node)
            
            if node ==self.goal:
                return self.get_results_dict(node)
            
            for move, successor in successors.items():
                if (successor not in self.frontier) and (successor not in self.explored):
                   self.parents[successor] = node
                   self.add_to_frontier_h3(successor)

        return self.get_results_dict(None)

    def h3_cost(self, node):
        
        t1 = node.find("1")
        t2 = node.find("2")
        t3 = node.find("3")
        t4 = node.find("4")
        t5 = node.find("5")
        t6 = node.find("6")
        t7 = node.find("7")
        t8 = node.find("8")

        sum_t1 = (abs(t1[0] - 1) + abs(t1[1] - 2)) * pow(1,2)
        sum_t2 = (abs(t2[0] - 2) + abs(t2[1] - 2)) * pow(2,2)
        sum_t3 = (abs(t3[0] - 0) + abs(t3[1] - 1)) * pow(3,2)
        sum_t4 = (abs(t4[0] - 1) + abs(t4[1] - 1)) * pow(4,2)
        sum_t5 = (abs(t5[0] - 2) + abs(t5[1] - 1)) * pow(5,2)
        sum_t6 = (abs(t6[0] - 0) + abs(t6[1] - 0)) * pow(6,2)
        sum_t7 = (abs(t7[0] - 1) + abs(t7[1] - 0)) * pow(7,2)
        sum_t8 = (abs(t8[0] - 2) + abs(t8[1] - 0)) * pow(8,2)

        sum_final = sum_t1 + sum_t2 + sum_t3 + sum_t4 + sum_t5 + sum_t6 + sum_t7 + sum_t8

        return sum_final

    def add_to_frontier_h3(self, node):
        """Add state to frontier and increase the frontier count."""
        self.frontier.add(node, self.h3_cost(node))
        self.frontier_count += 1

class A_Star(Greedy_Best_First):
    def __init__(self):
        self.goal = GOAL_STATE
        self.parents = {}  # state -> parent_state
        self.frontier = pdqpq.PriorityQueue()
        self.explored = set()
        self.frontier_count = 0  # increment when we add something to frontier
        self.expanded_count = 0  # increment when we pull something off frontier and expand
    
    def solve_astar_h1(self, start_state):
        self.parents[start_state] = None
        self.add_to_frontier_h1_astar(start_state)

        if start_state == self.goal:    
            return self.get_results_dict(start_state)

        while not self.frontier.is_empty():
            node = self.frontier.pop()
            
            if node == self.goal:
                return self.get_results_dict(node)

            successors = self.expand_node(node)

            for move, successor in successors.items():
                if (successor not in self.frontier) and (successor not in self.explored):
                    self.parents[successor] = node
                    self.add_to_frontier_h1_astar(successor)
                elif successor in self.frontier:
                    holder = self.parents[successor]
                    self.parents[successor] = node
                    if self.frontier.get(successor) > (self.h1_cost(successor) + self.get_cost(successor)):
                        self.frontier_update_h1_astar(successor)
                    else:
                        self.parents[successor] = holder

        return self.get_results_dict(None)

    def frontier_update_h1_astar(self, node):
        self.frontier.add(node, self.h1_cost(node) + self.get_cost(node))

    def add_to_frontier_h1_astar(self, node):
        """Add state to frontier and increase the frontier count."""
        self.frontier.add(node, self.h1_cost(node) + self.get_cost(node))
        self.frontier_count += 1
    
    def solve_astar_h2(self, start_state):
        self.parents[start_state] = None
        self.add_to_frontier_h2_astar(start_state)

        if start_state == self.goal:    
            return self.get_results_dict(start_state)

        while not self.frontier.is_empty():
            node = self.frontier.pop()
            
            if node == self.goal:
                return self.get_results_dict(node)

            successors = self.expand_node(node)

            for move, successor in successors.items():
                if (successor not in self.frontier) and (successor not in self.explored):
                    self.parents[successor] = node
                    self.add_to_frontier_h2_astar(successor)
                elif successor in self.frontier:
                    holder = self.parents[successor]
                    self.parents[successor] = node
                    if self.frontier.get(successor) > (self.h2_cost(successor) + self.get_cost(successor)):
                        self.frontier_update_h2_astar(successor)
                    else:
                        self.parents[successor] = holder

        return self.get_results_dict(None)
    
    def frontier_update_h2_astar(self, node):
        self.frontier.add(node, self.h2_cost(node) + self.get_cost(node))

    def add_to_frontier_h2_astar(self, node):
        """Add state to frontier and increase the frontier count."""
        self.frontier.add(node, self.h2_cost(node) + self.get_cost(node))
        self.frontier_count += 1

    def solve_astar_h3(self, start_state):
        self.parents[start_state] = None
        self.add_to_frontier_h3_astar(start_state)

        if start_state == self.goal:    
            return self.get_results_dict(start_state)

        while not self.frontier.is_empty():
            node = self.frontier.pop()
            
            if node == self.goal:
                return self.get_results_dict(node)

            successors = self.expand_node(node)

            for move, successor in successors.items():
                if (successor not in self.frontier) and (successor not in self.explored):
                    self.parents[successor] = node
                    self.add_to_frontier_h3_astar(successor)
                elif successor in self.frontier:
                    holder = self.parents[successor]
                    self.parents[successor] = node
                    if self.frontier.get(successor) > (self.h3_cost(successor) + self.get_cost(successor)):
                        self.frontier_update_h3_astar(successor)
                    else:
                        self.parents[successor] = holder

        return self.get_results_dict(None)

    def frontier_update_h3_astar(self, node):
        self.frontier.add(node, self.h3_cost(node) + self.get_cost(node))

    def add_to_frontier_h3_astar(self, node):
        """Add state to frontier and increase the frontier count."""
        self.frontier.add(node, self.h3_cost(node) + self.get_cost(node))
        self.frontier_count += 1

def print_table(flav__results, include_path=False):
    """Print out a comparison of search strategy results.

    Args:
        flav__results (dictionary): a dictionary mapping search flavor tags result statistics. See
            solve_puzzle() for detail.
        include_path (bool): indicates whether to include the actual solution paths in the table

    """
    result_tups = sorted(flav__results.items())
    c = len(result_tups)
    na = "{:>12}".format("n/a")
    rows = [  # abandon all hope ye who try to modify the table formatting code...
        "flavor  " + "".join([ "{:>12}".format(tag) for tag, _ in result_tups]),
        "--------" + ("  " + "-"*10)*c,
        "length  " + "".join([ "{:>12}".format(len(res['path'])) if 'path' in res else na 
                                for _, res in result_tups ]),
        "cost    " + "".join([ "{:>12,}".format(res['path_cost']) if 'path_cost' in res else na 
                                for _, res in result_tups ]),
        "frontier" + ("{:>12,}" * c).format(*[res['frontier_count'] for _, res in result_tups]),
        "expanded" + ("{:>12,}" * c).format(*[res['expanded_count'] for _, res in result_tups])
    ]
    if include_path:
        rows.append("path")
        longest_path = max([ len(res['path']) for _, res in result_tups if 'path' in res ] + [0])
        print("longest", longest_path)
        for i in range(longest_path):
            row = "        "
            for _, res in result_tups:
                if len(res.get('path', [])) > i:
                    move, state = res['path'][i]
                    row += " " + move[0] + " " + str(state)
                else:
                    row += " "*12
            rows.append(row)
    print("\n" + "\n".join(rows), "\n")


def get_test_puzzles():
    """Return sample start states for testing the search strategies.
    
    Returns:
        A tuple containing three EightPuzzleBoard objects representing start states that have an
        optimal solution path length of 3-5, 10-15, and >=25 respectively.
    
    """ 
    # Note: test cases can be hardcoded, and are not required to be programmatically generated.
    #
    # fill in function body here
    #    
    return (puzz.EightPuzzleBoard("125340678"), puzz.EightPuzzleBoard("154028367"), puzz.EightPuzzleBoard("082356174"))  # fix this line!

############################################

if __name__ == '__main__':

    # parse the command line args
    start = puzz.EightPuzzleBoard(sys.argv[1])
    if sys.argv[2] == 'all':
        flavors = ['bfs', 'ucost', 'greedy-h1', 'greedy-h2', 
                   'greedy-h3', 'astar-h1', 'astar-h2', 'astar-h3']
    else:
        flavors = sys.argv[2:]

    # run the search(es)
    results = {}
    for flav in flavors:
        print("Solving puzzle {} with {}".format(start, flav))
        results[flav] = solve_puzzle(start, flav)

    print_table(results, include_path = False)  # change to True to see the paths!


