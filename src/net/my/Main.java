package net.my;

import net.my.candidate.Candidate;
import net.my.item.Item;

import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<Candidate> candidates = new ArrayList<>();
        for (int i = 0; i < 20; i++) {
            candidates.add(Candidate.generateCandidate());
        }

        for (Candidate candidate : candidates) {
            System.out.println("Weight: "+candidate.getTotalWeight()+" Value: "+candidate.getTotalValue());
        }
    }
}