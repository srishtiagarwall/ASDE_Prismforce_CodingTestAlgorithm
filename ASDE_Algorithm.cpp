def can_cross_chakravyuh(p, enemies, skip, recharge):
    // Power levels of enemies in each circle
    k = enemies.copy()

    // Check initial power
    if p <= 0:
        return False

    // Track skips and recharges
    skips_left = skip
    recharges_left = recharge

    for i in range(len(k)):
        if p > k[i]:
            // If Abhimanyu has more power, he can defeat the enemy
            p -= k[i]
        else:
            if skips_left > 0:
                // If he cannot defeat the enemy but has skips left, use a skip
                skips_left -= 1
            elif recharges_left > 0:
                // If he cannot skip but has recharges left, use a recharge
                recharges_left -= 1
                // Assume recharge gives full power (this is an assumption as recharge power is not defined)
                p = max(p, k[i] + 1)  // Ensures he can defeat the current enemy after recharging
                p -= k[i]
            else:
                // If no skips or recharges left, he loses the battle
                return False
        
        // Handle regenerating enemies (k3 and k7)
        if i == 2 or i == 6:
            regenerated_power = k[i] // 2
            if p > regenerated_power:
                // If Abhimanyu has more power, he can defeat the regenerating enemy
                p -= regenerated_power
            else:
                if skips_left > 0:
                    skips_left -= 1
                elif recharges_left > 0:
                    recharges_left -= 1
                    p = max(p, regenerated_power + 1)
                    p -= regenerated_power
                else:
                    return False

    return True

// Test the algorithm with two sets of test cases
test_cases = [
    {'p': 50, 'enemies': [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55], 'skip': 2, 'recharge': 2},
    {'p': 30, 'enemies': [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110], 'skip': 1, 'recharge': 1}
]

for i, test in enumerate(test_cases):
    result = can_cross_chakravyuh(test['p'], test['enemies'], test['skip'], test['recharge'])
    print(f"Test Case {i+1}: {'Success' if result else 'Failure'}")
