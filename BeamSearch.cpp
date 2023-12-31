// BeamSearch.cpp

#include "BeamSearch.h"
extern std::chrono::duration<double> timeTry;
extern std::chrono::duration<double> timeCC1;
extern std::chrono::duration<double> timeCC2;
double weightControl = 0.9;
double weightControl2 = 0.1;

////beam search without weight
//BeamSearch::BeamSearch(const std::vector<double>& distances, const std::vector<double>& angles)
//    : distances(distances), angles(angles) {
//}
//std::vector<std::vector<double>> BeamSearch::runSearch(int sequence_beam_width) {
//
//    std::vector<std::vector<double>> result;
//    beam_width = sequence_beam_width;
//    max_length = angles.size();
//    std::priority_queue<State> beam;
//
//    //处理第一个角度
//    std::vector<double> sequence1 = { angles[0] };
//    Collision_check collisionChecker1;
//    if (!collisionChecker1.checkCollision3(distances, sequence1, 0, 1))//碰撞检测无
//    {
//        std::vector<double> type1 = { 0 };
//        beam.push(State(sequence1, 0.0, type1));
//    }
//    else {//碰撞
//        for (int i = 1; i <= 150; i++)
//        {
//            double angle_change1 = angles[0] + i;
//            std::vector<double> sequence2 = { angle_change1 };
//            Collision_check collisionChecker2;
//            if (!collisionChecker2.checkCollision3(distances, sequence2, 0, 1))
//            {
//                std::vector<double> type2 = { 1 };
//                beam.push(State(sequence2, 1.0, type2));
//                break;
//            }
//            double angle_change2 = angles[0] - i;
//            std::vector<double> sequence3 = { angle_change2 };
//            Collision_check collisionChecker21;
//            if (!collisionChecker21.checkCollision3(distances, sequence3, 0, 1))
//            {
//                std::vector<double> type3 = { 1 };
//                beam.push(State(sequence3, 1.0, type3));
//                break;
//            }
//        }
//    }
//    int finish_angle = 1;
//    //
//    while (!beam.empty())
//    {
//        // Get the top-k candidates from the beam
//        std::vector<State> candidates;
//        for (int i = 0; i < beam_width; i++) {
//            if (!beam.empty()) {
//                candidates.push_back(beam.top());
//                beam.pop();
//            }
//        }
//        beam = std::priority_queue<State>();//清空
//
//        // Expand each candidate and add new candidates to the beam
//        for (const State& candidate : candidates)
//        {
//            if (candidate.sequence.size() >= max_length)
//            {
//                result.push_back(candidate.sequence);
//            }
//            else
//            {
//                int alreadynum = candidate.sequence.size();
//                std::vector<double> new_sequence = candidate.sequence; 
//                new_sequence.push_back(angles[alreadynum]);
//                Collision_check collisionChecker3;
//                //碰撞检测无
//                if (!collisionChecker3.checkCollision3(distances, new_sequence, 0, alreadynum + 1))
//                {
//                    std::vector<double> new_type = candidate.type;
//                    new_type.push_back(0);
//                    double new_score = candidate.score; 
//                    beam.push(State(new_sequence, new_score, new_type));
//                }
//                else
//                {
//                    //type=1  改变自身
//                    bool type_1_ok = 0;
//                    for (int i = 1; i <= 150; i++)
//                    {
//                        double angle_change3 = angles[alreadynum] + i;
//                        std::vector<double> new_sequence2 = candidate.sequence;
//                        new_sequence2.push_back(angle_change3);
//                        Collision_check collisionChecker4;
//                        if (!collisionChecker4.checkCollision3(distances, new_sequence2, 0, alreadynum + 1))
//                        {
//                            std::vector<double> new_type2 = candidate.type;
//                            new_type2.push_back(1);
//                            double new_score2 = candidate.score + 1;
//                            beam.push(State(new_sequence2, new_score2, new_type2));
//                            type_1_ok = 1;
//                            break;
//                        }
//                        double angle_change4 = angles[alreadynum] - i;
//                        std::vector<double> new_sequence3 = candidate.sequence;
//                        new_sequence3.push_back(angle_change4);
//                        Collision_check collisionChecker5;
//                        if (!collisionChecker5.checkCollision3(distances, new_sequence3, 0, alreadynum + 1))
//                        {
//                            std::vector<double> new_type3 = candidate.type;
//                            new_type3.push_back(1);
//                            double new_score3 = candidate.score + 1;
//                            beam.push(State(new_sequence3, new_score3, new_type3));
//                            type_1_ok = 1;
//                            break;
//                        }
//                    }
//                    //只改变自己不行 全部都改
//                    if (!type_1_ok)
//                    {
//                        std::vector<double> new_type4 = candidate.type;
//                        std::vector<double> open_point;
//                        new_type4.push_back(1);
//                        int count = 0;
//                        for (int i = 0; i < new_type4.size(); i++) {
//                            if (new_type4[i] == 1.0) {
//                                open_point.push_back(i); // 记录满足条件的位置
//                            }
//                        }
//                        count = open_point.size();
//                        //改变所有开点（包括目前的）找到合适
//                        //int limit = static_cast<int>(std::pow(150, count));
//                        std::vector<double> new_sequence4 = candidate.sequence;
//                        new_sequence4.push_back(angles[alreadynum]);
//                        bool find_ok = 0;
//                        auto start_try = std::chrono::high_resolution_clock::now();
//                        for (int j = 0; j < count; j++)
//                        {
//
//                            for (int k = 0; k < 150; k++) {
//                                Collision_check collisionChecker6;
//                                new_sequence4[open_point[j]] += k;
//                                if (!collisionChecker6.checkCollision2(distances, new_sequence4, 0, alreadynum + 1))
//                                {
//                                    double new_score4 = candidate.score + 1;
//                                    beam.push(State(new_sequence4, new_score4, new_type4));
//                                    find_ok = 1;
//                                    break;
//                                }
//                                new_sequence4[open_point[j]] -= 2 * k;
//                                Collision_check collisionChecker7;
//                                if (!collisionChecker7.checkCollision2(distances, new_sequence4, 0, alreadynum + 1))
//                                {
//                                    double new_score41 = candidate.score + 1;
//                                    beam.push(State(new_sequence4, new_score41, new_type4));
//                                    find_ok = 1;
//                                    break;
//                                }
//                                new_sequence4[open_point[j]] += k;
//                            }
//                            if (find_ok)
//                            {
//                                break;
//                            }
//                        }
//                        auto end_try = std::chrono::high_resolution_clock::now();
//                        timeTry += end_try - start_try;
//                    }
//
//                    //type=0  //改变前面所有开点
//                    std::vector<double> new_type5 = candidate.type;
//                    new_type5.push_back(0);
//                    int count2 = 0;
//                    std::vector<double> open_point2;
//                    for (int i = 0; i < new_type5.size(); i++)
//                    {
//                        if (new_type5[i] == 1.0) {
//                            open_point2.push_back(i); // 记录满足条件的位置
//                        }
//                    }
//                    count2 = open_point2.size();
//                    //int limit2 = static_cast<int>(std::pow(150, count2));
//                    std::vector<double> new_sequence5 = candidate.sequence;
//                    new_sequence5.push_back(angles[alreadynum]);
//                    bool find_ok2 = 0;
//                    auto start_try2 = std::chrono::high_resolution_clock::now();
//                    for (int j = 0; j < count2; j++)
//                    {
//                        for (int k = 0; k < 150; k++) {
//                            Collision_check collisionChecker8;
//                            new_sequence5[open_point2[j]] += k;
//                            if (!collisionChecker8.checkCollision2(distances, new_sequence5, 0, alreadynum + 1))
//                            {
//                                double new_score5 = candidate.score;
//                                beam.push(State(new_sequence5, new_score5, new_type5));
//                                find_ok2 = 1;
//                                break;
//                            }
//                            new_sequence5[open_point2[j]] -= 2 * k;
//                            Collision_check collisionChecker9;
//                            if (!collisionChecker9.checkCollision2(distances, new_sequence5, 0, alreadynum + 1))
//                            {
//                                double new_score51 = candidate.score;
//                                beam.push(State(new_sequence5, new_score51, new_type5));
//                                find_ok2 = 1;
//                                break;
//                            }
//                            new_sequence5[open_point2[j]] += k;
//                        }
//                        if (find_ok2)
//                        {
//                            break;
//                        }
//                    }
//                    auto end_try2 = std::chrono::high_resolution_clock::now();
//                    timeTry += end_try2 - start_try2;
//
//                }
//
//                ////type=0  //改变前面所有开点
//                //std::vector<double> new_type5 = candidate.type;
//                //new_type5.push_back(0);
//                //int count2 = 0;
//                //std::vector<double> open_point2;
//                //for (int i = 0; i < new_type5.size(); i++) 
//                //{
//                //    if (new_type5[i] == 1.0) {
//                //        open_point2.push_back(i); // 记录满足条件的位置
//                //    }
//                //}
//                //count2 = open_point2.size();
//                ////int limit2 = static_cast<int>(std::pow(150, count2));
//                //std::vector<double> new_sequence5 = candidate.sequence;
//                //new_sequence5.push_back(angles[alreadynum]);
//                //bool find_ok2 = 0;
//                //for (int j = 0; j < count2; j++)
//                //{
//                //    for (int k = 0; k < 150; k++) {
//                //        Collision_check collisionChecker8;
//                //        new_sequence5[open_point2[j]] += k;
//                //        if (!collisionChecker8.checkCollision(distances, new_sequence5, 0, alreadynum + 1))
//                //        {
//                //            double new_score5 = candidate.score;
//                //            beam.push(State(new_sequence5, new_score5, new_type5));
//                //            find_ok2 = 1;
//                //            break;
//                //        }
//                //        new_sequence5[open_point2[j]] -= 2 * k;
//                //        Collision_check collisionChecker9;
//                //        if (!collisionChecker9.checkCollision(distances, new_sequence5, 0, alreadynum + 1))
//                //        {
//                //            double new_score51 = candidate.score;
//                //            beam.push(State(new_sequence5, new_score51, new_type5));
//                //            find_ok2 = 1;
//                //            break;
//                //        }
//                //        new_sequence5[open_point2[j]] += k;
//                //    }
//                //    if (find_ok2)
//                //    {
//                //        break;
//                //    }
//                //}
//            }
//            // Here, you can generate new candidates and compute their scores
//            // For simplicity, we use a placeholder function that generates random candidates
//            //for (int i = 0; i < beam_width; i++) {
//            //    std::vector<double> new_sequence = candidate.sequence; // Generate a random candidate
//            //    new_sequence.push_back(i);
//            //    std::vector<double> new_type = candidate.type;
//            //    new_type.push_back(i);
//            //    double new_score = candidate.score - i; // Calculate a random score
//            //    beam.push(State(new_sequence, new_score, new_type));
//            //}
//        }
//        finish_angle++;
//        std::cout << finish_angle << " ";
//    }
//
//    // Sort and return the top-k results
//    std::sort(result.begin(), result.end());
//    std::cout << "ok" << std::endl;
//
//    return result;
//}
//std::vector<double> BeamSearch::getBendingSequence()
//{
//    size_t numAngles = angles.size();
//    int bendingtimes = 0;
//    std::vector<double> angles_change = angles;
//    std::vector<double> angles_change_dir(numAngles, 0);
//
//    for (bendingtimes = 0; bendingtimes < numAngles; bendingtimes++)
//    {
//        Collision_check collisionChecker;
//        if (!collisionChecker.checkCollision(distances, angles_change, 0, bendingtimes + 1))//0-1 1个角
//        {
//            angles_change_dir[bendingtimes] = 0;
//        }
//        else {
//            angles_change_dir[bendingtimes] = 1;
//        }
//
//        if (angles_change_dir[bendingtimes] == 1)
//        {
//            for (int i = 0; i < bendingtimes; i++)//默认第一个可行
//            {
//                for (int j = 0; j <= 150; j++)
//                {
//                    Collision_check collisionChecker1;
//                    angles_change[i] += j;
//                    if (!collisionChecker1.checkCollision(distances, angles_change, 0, bendingtimes + 1))
//                    {
//                        angles_change_dir[bendingtimes] = 0;
//                        angles_change_dir[i] = 1;
//                        break;
//                    }
//                    angles_change[i] -= 2 * j;
//                    Collision_check collisionChecker2;
//                    if (!collisionChecker2.checkCollision(distances, angles_change, 0, bendingtimes + 1))
//                    {
//                        angles_change_dir[bendingtimes] = 0;
//                        angles_change_dir[i] = 1;
//                        break;
//                    }
//                    angles_change[i] += j;
//                }
//                Collision_check collisionChecker3;
//                if (!collisionChecker3.checkCollision(distances, angles_change, 0, bendingtimes + 1))
//                {
//                    break;
//                }
//            }
//
//        }
//        std::cout << bendingtimes + 1 << std::endl;
//    }
//    Collision_check collisionChecker4;
//    if (!collisionChecker4.checkCollision(distances, angles_change, 0, numAngles))
//    {
//        std::cout << "ok" << std::endl;
//    }
//    for (const double& value : angles_change) {
//        std::cout << value << " ";
//    }
//    std::cout << std::endl;
//
//    return angles_change_dir;
//}
//std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>>> BeamSearch::getBendingSpace(int angle_start, int angle_end)//start离散 end为连续space
//{
//    //size_t numAngles = angles.size();
//    std::pair<int, int> pair1 = std::make_pair(angle_start, angle_end);//调整
//    double angle_start_num = angles[angle_start];
//    //double angle_end_num = angles[angle_end];
//    double angle_end_space1, angle_end_space2;
//    std::vector<double> angles_changed = angles;
//
//    for (int i = -150; i <= 150; i = i + 5)
//    {
//        std::pair<int, int> pair2, pair3;
//        bool findsolution = false;
//        bool findsolution_pair = false;
//        angle_start_num = i;
//        angles_changed[angle_end] = angle_start_num;//调整
//
//        for (int j = -150; j <= 150; j++)
//        {
//
//            angles_changed[angle_start] = j;//调整
//            Collision_check collisionChecker1;
//            if (!collisionChecker1.checkCollision(distances, angles_changed, angle_start, angle_end + 2) && !findsolution)
//            {
//                findsolution = true;
//                angle_end_space1 = j;
//            }
//            Collision_check collisionChecker2;
//            if (collisionChecker2.checkCollision(distances, angles_changed, angle_start, angle_end + 2) && findsolution)
//            {
//                angle_end_space2 = j--;
//                findsolution_pair = true;
//            }
//            if (findsolution_pair)
//            {
//                pair2 = std::make_pair(angle_start, angle_start_num);
//                pair3 = std::make_pair(angle_end_space1, angle_end_space2);
//                std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>> data1(pair1, pair2, pair3);
//
//                //输出data1
//                std::cout << std::get<0>(data1).first << " " << std::get<0>(data1).second << " " << std::get<1>(data1).first << " " << std::get<1>(data1).second << " " << std::get<2>(data1).first << " " << std::get<2>(data1).second << std::endl;
//
//                bendingrange.push_back(data1);
//                findsolution_pair = false;
//                findsolution = false;
//            }
//
//        }
//
//        std::cout << i << "ok";
//    }
//
//    return bendingrange;
//}
//

////beam search with weight
//BeamSearch::BeamSearch(const std::vector<double>& distances, const std::vector<double>& angles, const std::vector<double>& collisionAnglesSeq)
//    : distances(distances), angles(angles), collisionAnglesSeq(collisionAnglesSeq) {
//}
//int BeamSearch::countMatchingOnes(const std::vector<double>& collisionAnglesSeq, const std::vector<double>& type) {
//    int count = 0;
//
//    // 确保两个序列大小相同或取最小大小以避免越界
//    size_t minSize = std::min(collisionAnglesSeq.size(), type.size());
//
//    //权重[0,1]
//    for (size_t i = 0; i < minSize; ++i) {
//        if (collisionAnglesSeq[i] != 0.0 && type[i] == 1.0) {
//            count+= collisionAnglesSeq[i];
//        }
//    }
//
//    ////权重0/1
//    //for (size_t i = 0; i < minSize; ++i) {
//    //    if (collisionAnglesSeq[i] != 0.0 && type[i] == 1.0) {
//    //        count ++;
//    //    }
//    //}
//
//    ////without weight
//    //for (size_t i = 0; i < minSize; ++i) {
//    //    if (collisionAnglesSeq[i] == 1.0 && type[i] == 1.0) {
//    //        count++;
//    //    }
//    //}
//
//    return count;
//}
//std::vector<std::vector<double>> BeamSearch::runSearch(int sequence_beam_width) {
//
//    std::vector<std::vector<double>> result;
//    beam_width = sequence_beam_width;
//    max_length = angles.size();
//    std::priority_queue<State> beam;
//
//    bool pruning = 0;
//    std::set<double> uniqueValues;
//    for (const auto& value : collisionAnglesSeq) {
//        uniqueValues.insert(value);
//    }
//    if (uniqueValues.size() == 2)
//    {
//        pruning = 1;
//    }
//
//    //处理第一个角度
//    std::vector<double> sequence1 = { angles[0] };
//    Collision_check collisionChecker1;
//    if (!collisionChecker1.checkCollision3(distances, sequence1, 0, 1))//碰撞检测无
//    {
//        std::vector<double> type1 = { 0 };
//        int matchnum1=countMatchingOnes(collisionAnglesSeq, type1);
//        beam.push(State(sequence1, 0.0, type1, matchnum1));
//    }
//    else {//碰撞
//        for (int i = 1; i <= 150; i++)
//        {
//            double angle_change1 = angles[0] + i;
//            std::vector<double> sequence2 = { angle_change1 };
//            Collision_check collisionChecker2;
//            if (!collisionChecker2.checkCollision3(distances, sequence2, 0, 1))
//            {
//                std::vector<double> type2 = { 1 };
//                int matchnum2 = countMatchingOnes(collisionAnglesSeq, type2);
//                beam.push(State(sequence2, 1.0, type2, matchnum2));
//                break;
//            }
//            double angle_change2 = angles[0] - i;
//            std::vector<double> sequence3 = { angle_change2 };
//            Collision_check collisionChecker21;
//            if (!collisionChecker21.checkCollision3(distances, sequence3, 0, 1))
//            {
//                std::vector<double> type3 = { 1 };
//                int matchnum3 = countMatchingOnes(collisionAnglesSeq, type3);
//                beam.push(State(sequence3, 1.0, type3, matchnum3));
//                break;
//            }
//        }
//    }
//    int finish_angle = 1;
//    //
//    while (!beam.empty()) 
//    {
//        // Get the top-k candidates from the beam
//        std::vector<State> candidates;
//        for (int i = 0; i < beam_width; i++) {
//            if (!beam.empty()) {
//                candidates.push_back(beam.top());
//                beam.pop();
//            }
//        }
//        beam = std::priority_queue<State>();//清空
//
//        // Expand each candidate and add new candidates to the beam
//        for (const State& candidate : candidates) 
//        {
//            if (candidate.sequence.size() >= max_length) 
//            {
//                result.push_back(candidate.sequence);
//            }
//            else 
//            {
//                int alreadynum = candidate.sequence.size();
//                std::vector<double> new_sequence = candidate.sequence; 
//                new_sequence.push_back(angles[alreadynum]);
//                Collision_check collisionChecker3;
//                //碰撞检测无
//                if (!collisionChecker3.checkCollision3(distances, new_sequence, 0, alreadynum + 1))
//                {
//                    std::vector<double> new_type = candidate.type;
//                    new_type.push_back(0);
//                    double new_score = candidate.score; // Calculate a random score
//                    int matchnum_new = countMatchingOnes(collisionAnglesSeq, new_type);
//                    beam.push(State(new_sequence, new_score, new_type, matchnum_new));
//                }
//                else 
//                {
//                    //type=1 
//                    if ((collisionAnglesSeq[alreadynum] > weightControl2) || pruning)  //减少cro
//                    {
//                        //type=1  改变自身
//                        bool type_1_ok = 0;
//                        for (int i = 1; i <= 150; i++)
//                        {
//                            double angle_change3 = angles[alreadynum] + i;
//                            std::vector<double> new_sequence2 = candidate.sequence;
//                            new_sequence2.push_back(angle_change3);
//                            Collision_check collisionChecker4;
//                            if (!collisionChecker4.checkCollision3(distances, new_sequence2, 0, alreadynum + 1))
//                            {
//                                std::vector<double> new_type2 = candidate.type;
//                                new_type2.push_back(1);
//                                double new_score2 = candidate.score + 1;
//                                int matchnum_new2 = countMatchingOnes(collisionAnglesSeq, new_type2);
//                                beam.push(State(new_sequence2, new_score2, new_type2, matchnum_new2));
//                                type_1_ok = 1;
//                                break;
//                            }
//                            double angle_change4 = angles[alreadynum] - i;
//                            std::vector<double> new_sequence3 = candidate.sequence;
//                            new_sequence3.push_back(angle_change4);
//                            Collision_check collisionChecker5;
//                            if (!collisionChecker5.checkCollision3(distances, new_sequence3, 0, alreadynum + 1))
//                            {
//                                std::vector<double> new_type3 = candidate.type;
//                                new_type3.push_back(1);
//                                double new_score3 = candidate.score + 1;
//                                int matchnum_new3 = countMatchingOnes(collisionAnglesSeq, new_type3);
//                                beam.push(State(new_sequence3, new_score3, new_type3, matchnum_new3));
//                                type_1_ok = 1;
//                                break;
//                            }
//                        }
//                        //只改变自己不行 全部都改
//                        if (!type_1_ok)
//                        {
//                            std::vector<double> new_type4 = candidate.type;
//                            std::vector<double> open_point;
//                            new_type4.push_back(1);
//                            int count = 0;
//                            for (int i = 0; i < new_type4.size(); i++) {
//                                if (new_type4[i] == 1.0) {
//                                    open_point.push_back(i); // 记录满足条件的位置
//                                }
//                            }
//                            count = open_point.size();
//                            //改变所有开点（包括目前的）找到合适
//                            //int limit = static_cast<int>(std::pow(150, count));
//                            std::vector<double> new_sequence4 = candidate.sequence;
//                            new_sequence4.push_back(angles[alreadynum]);
//                            bool find_ok = 0;
//                            auto start_try = std::chrono::high_resolution_clock::now();
//                            for (int j = 0; j < count; j++)
//                            {
//
//                                for (int k = 0; k < 150; k++) {
//                                    Collision_check collisionChecker6;
//                                    new_sequence4[open_point[j]] += k;
//                                    if (!collisionChecker6.checkCollision2(distances, new_sequence4, 0, alreadynum + 1))
//                                    {
//                                        double new_score4 = candidate.score + 1;
//                                        int matchnum_new4 = countMatchingOnes(collisionAnglesSeq, new_type4);
//                                        beam.push(State(new_sequence4, new_score4, new_type4, matchnum_new4));
//                                        find_ok = 1;
//                                        break;
//                                    }
//                                    new_sequence4[open_point[j]] -= 2 * k;
//                                    Collision_check collisionChecker7;
//                                    if (!collisionChecker7.checkCollision2(distances, new_sequence4, 0, alreadynum + 1))
//                                    {
//                                        double new_score41 = candidate.score + 1;
//                                        int matchnum_new41 = countMatchingOnes(collisionAnglesSeq, new_type4);
//                                        beam.push(State(new_sequence4, new_score41, new_type4, matchnum_new41));
//                                        find_ok = 1;
//                                        break;
//                                    }
//                                    new_sequence4[open_point[j]] += k;
//                                }
//                                if (find_ok)
//                                {
//                                    break;
//                                }
//                            }
//                            auto end_try = std::chrono::high_resolution_clock::now();
//                            timeTry += end_try - start_try;
//                        }
//                    }
//
//
//                    //type=0  //改变前面所有开点
//                    if ((collisionAnglesSeq[alreadynum] < weightControl) || pruning)  //减少cro
//                    {
//                        std::vector<double> new_type5 = candidate.type;
//                        new_type5.push_back(0);
//                        int count2 = 0;
//                        std::vector<double> open_point2;
//                        for (int i = 0; i < new_type5.size(); i++)
//                        {
//                            if (new_type5[i] == 1.0) {
//                                open_point2.push_back(i); // 记录满足条件的位置
//                            }
//                        }
//                        count2 = open_point2.size();
//                        //int limit2 = static_cast<int>(std::pow(150, count2));
//                        std::vector<double> new_sequence5 = candidate.sequence;
//                        new_sequence5.push_back(angles[alreadynum]);
//                        bool find_ok2 = 0;
//                        auto start_try2 = std::chrono::high_resolution_clock::now();
//                        for (int j = 0; j < count2; j++)
//                        {
//                            for (int k = 0; k < 150; k++)
//                            {
//                                Collision_check collisionChecker8;
//                                new_sequence5[open_point2[j]] += k;
//                                if (!collisionChecker8.checkCollision2(distances, new_sequence5, 0, alreadynum + 1))
//                                {
//                                    double new_score5 = candidate.score;
//                                    int matchnum_new5 = countMatchingOnes(collisionAnglesSeq, new_type5);
//                                    beam.push(State(new_sequence5, new_score5, new_type5, matchnum_new5));
//                                    find_ok2 = 1;
//                                    break;
//                                }
//                                new_sequence5[open_point2[j]] -= 2 * k;
//                                Collision_check collisionChecker9;
//                                if (!collisionChecker9.checkCollision2(distances, new_sequence5, 0, alreadynum + 1))
//                                {
//                                    double new_score51 = candidate.score;
//                                    int matchnum_new51 = countMatchingOnes(collisionAnglesSeq, new_type5);
//                                    beam.push(State(new_sequence5, new_score51, new_type5, matchnum_new51));
//                                    find_ok2 = 1;
//                                    break;
//                                }
//                                new_sequence5[open_point2[j]] += k;
//                            }
//                            if (find_ok2)
//                            {
//                                break;
//                            }
//                        }
//                        auto end_try2 = std::chrono::high_resolution_clock::now();
//                        timeTry += end_try2 - start_try2;
//                    }
//                }
//
//                    ////type=0  //改变前面所有开点
//                    //std::vector<double> new_type5 = candidate.type;
//                    //new_type5.push_back(0);
//                    //int count2 = 0;
//                    //std::vector<double> open_point2;
//                    //for (int i = 0; i < new_type5.size(); i++) 
//                    //{
//                    //    if (new_type5[i] == 1.0) {
//                    //        open_point2.push_back(i); // 记录满足条件的位置
//                    //    }
//                    //}
//                    //count2 = open_point2.size();
//                    ////int limit2 = static_cast<int>(std::pow(150, count2));
//                    //std::vector<double> new_sequence5 = candidate.sequence;
//                    //new_sequence5.push_back(angles[alreadynum]);
//                    //bool find_ok2 = 0;
//                    //for (int j = 0; j < count2; j++)
//                    //{
//                    //    for (int k = 0; k < 150; k++) {
//                    //        Collision_check collisionChecker8;
//                    //        new_sequence5[open_point2[j]] += k;
//                    //        if (!collisionChecker8.checkCollision(distances, new_sequence5, 0, alreadynum + 1))
//                    //        {
//                    //            double new_score5 = candidate.score;
//                    //            beam.push(State(new_sequence5, new_score5, new_type5));
//                    //            find_ok2 = 1;
//                    //            break;
//                    //        }
//                    //        new_sequence5[open_point2[j]] -= 2 * k;
//                    //        Collision_check collisionChecker9;
//                    //        if (!collisionChecker9.checkCollision(distances, new_sequence5, 0, alreadynum + 1))
//                    //        {
//                    //            double new_score51 = candidate.score;
//                    //            beam.push(State(new_sequence5, new_score51, new_type5));
//                    //            find_ok2 = 1;
//                    //            break;
//                    //        }
//                    //        new_sequence5[open_point2[j]] += k;
//                    //    }
//                    //    if (find_ok2)
//                    //    {
//                    //        break;
//                    //    }
//                    //}
//            }
//        }
//        finish_angle++;
//        std::cout << finish_angle << " ";
//    }
//
//    // Sort and return the top-k results
//    std::sort(result.begin(), result.end());
//    std::cout << "ok" << std::endl;
//
//    return result;
//}
//std::vector<double> BeamSearch::getBendingSequence()
//{
//    size_t numAngles = angles.size();
//    int bendingtimes = 0;
//    std::vector<double> angles_change = angles;
//    std::vector<double> angles_change_dir(numAngles,0);
//    
//    for (bendingtimes = 0; bendingtimes < numAngles; bendingtimes++)
//    {
//        Collision_check collisionChecker;
//        if (!collisionChecker.checkCollision(distances, angles_change, 0, bendingtimes+1))//0-1 1个角
//        {
//            angles_change_dir[bendingtimes] = 0;
//        } 
//        else {
//            angles_change_dir[bendingtimes] = 1;
//        }
//
//        if (angles_change_dir[bendingtimes] == 1)
//        {
//            for (int i = 0; i < bendingtimes; i++)//默认第一个可行
//            {
//                for (int j = 0; j <= 150; j++)
//                {
//                    Collision_check collisionChecker1;
//                    angles_change[i] += j;
//                    if (!collisionChecker1.checkCollision(distances, angles_change, 0, bendingtimes + 1))
//                    {
//                        angles_change_dir[bendingtimes] = 0;
//                        angles_change_dir[i] = 1;
//                        break;
//                    }
//                    angles_change[i] -= 2*j;
//                    Collision_check collisionChecker2;
//                    if (!collisionChecker2.checkCollision(distances, angles_change, 0, bendingtimes + 1))
//                    {
//                        angles_change_dir[bendingtimes] = 0;
//                        angles_change_dir[i] = 1;
//                        break;
//                    }
//                    angles_change[i] += j;
//                }
//                Collision_check collisionChecker3;
//                if (!collisionChecker3.checkCollision(distances, angles_change, 0, bendingtimes + 1))
//                {
//                    break;
//                }
//            }
//
//        }
//        std::cout << bendingtimes + 1 << std::endl;
//    }
//    Collision_check collisionChecker4;
//    if (!collisionChecker4.checkCollision(distances, angles_change, 0, numAngles ))
//    {
//        std::cout<<"ok"<<std::endl;
//    }
//    for (const double& value : angles_change) {
//        std::cout << value << " ";
//    }
//    std::cout << std::endl;
//    
//    return angles_change_dir;
//}
//std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>>> BeamSearch::getBendingSpace(int angle_start, int angle_end)//start离散 end为连续space
//{
//    //size_t numAngles = angles.size();
//    std::pair<int, int> pair1 = std::make_pair(angle_start, angle_end);//调整
//    double angle_start_num = angles[angle_start];
//    //double angle_end_num = angles[angle_end];
//    double angle_end_space1, angle_end_space2;
//    std::vector<double> angles_changed= angles;
//    
//    for(int i=-150;i<=150;i=i+5)
//    {
//        std::pair<int, int> pair2, pair3;
//        bool findsolution = false;
//        bool findsolution_pair = false;
//        angle_start_num = i;
//        angles_changed[angle_end] = angle_start_num;//调整
//
//        for (int j = -150; j <= 150; j++)
//        {
//
//            angles_changed[angle_start] = j;//调整
//            Collision_check collisionChecker1;
//            if (!collisionChecker1.checkCollision(distances, angles_changed, angle_start, angle_end+2)&&!findsolution)
//            {
//				findsolution = true;
//                angle_end_space1 = j;
//			}
//            Collision_check collisionChecker2;
//            if (collisionChecker2.checkCollision(distances, angles_changed, angle_start, angle_end +2) && findsolution)
//            {
//				angle_end_space2 = j--;
//                findsolution_pair= true;
//			}
//            if(findsolution_pair)
//            {
//                pair2 = std::make_pair(angle_start, angle_start_num);
//                pair3 = std::make_pair(angle_end_space1, angle_end_space2);
//                std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>> data1(pair1, pair2, pair3);
//
//                //输出data1
//                std::cout << std::get<0>(data1).first << " " << std::get<0>(data1).second << " " << std::get<1>(data1).first << " " << std::get<1>(data1).second << " " << std::get<2>(data1).first << " " << std::get<2>(data1).second << std::endl;
//
//                bendingrange.push_back(data1);
//                findsolution_pair = false;
//                findsolution = false;
//            }
//
//        }
//
//    std::cout << i << "ok";
//    }
//
//    return bendingrange;
//}

//beam search without weight freeform
BeamSearch::BeamSearch(const std::vector<ShapeElement>& ShapeElements, const std::vector<double>& angles)
    : ShapeElements(ShapeElements), angles(angles) {
}
std::vector<std::vector<double>> BeamSearch::runSearch(int sequence_beam_width) {

    for (const auto& element : ShapeElements) {
        distances.push_back(element.forwordLength);
        curvature.push_back(element.curvature);
        if (element.type == "segment")
        {
			segArc.push_back(0);
		}
        else
        {
			segArc.push_back(1);
		}
    }

    std::vector<std::vector<double>> result;
    beam_width = sequence_beam_width;
    max_length = angles.size();
    std::priority_queue<State> beam;

    //处理第一个角度
    std::vector<double> sequence1 = { angles[0] };
    Collision_check collisionChecker1;
    if (!collisionChecker1.checkCollision4(distances, sequence1, 0, 1, segArc, curvature))//碰撞检测无
    {
        std::vector<double> type1 = { 0 };
        beam.push(State(sequence1, 0.0, type1));
    }
    else {//碰撞
        for (int i = 1; i <= 150; i++)
        {
            double angle_change1 = angles[0] + i;
            std::vector<double> sequence2 = { angle_change1 };
            Collision_check collisionChecker2;
            if (!collisionChecker2.checkCollision4(distances, sequence2, 0, 1, segArc, curvature))
            {
                std::vector<double> type2 = { 1 };
                beam.push(State(sequence2, 1.0, type2));
                break;
            }
            double angle_change2 = angles[0] - i;
            std::vector<double> sequence3 = { angle_change2 };
            Collision_check collisionChecker21;
            if (!collisionChecker21.checkCollision4(distances, sequence3, 0, 1, segArc, curvature))
            {
                std::vector<double> type3 = { 1 };
                beam.push(State(sequence3, 1.0, type3));
                break;
            }
        }
    }
    int finish_angle = 1;
    //
    while (!beam.empty())
    {
        // Get the top-k candidates from the beam
        std::vector<State> candidates;
        for (int i = 0; i < beam_width; i++) {
            if (!beam.empty()) {
                candidates.push_back(beam.top());
                beam.pop();
            }
        }
        beam = std::priority_queue<State>();//清空

        // Expand each candidate and add new candidates to the beam
        for (const State& candidate : candidates)
        {
            if (candidate.sequence.size() >= max_length)
            {
                result.push_back(candidate.sequence);
            }
            else
            {
                int alreadynum = candidate.sequence.size();
                std::vector<double> new_sequence = candidate.sequence;
                new_sequence.push_back(angles[alreadynum]);
                Collision_check collisionChecker3;
                //碰撞检测无
                if (!collisionChecker3.checkCollision4(distances, new_sequence, 0, alreadynum + 1, segArc, curvature))
                {
                    std::vector<double> new_type = candidate.type;
                    new_type.push_back(0);
                    double new_score = candidate.score;
                    beam.push(State(new_sequence, new_score, new_type));
                }
                else
                {
                    //type=1  改变自身
                    bool type_1_ok = 0;
                    for (int i = 1; i <= 150; i++)
                    {
                        double angle_change3 = angles[alreadynum] + i;
                        std::vector<double> new_sequence2 = candidate.sequence;
                        new_sequence2.push_back(angle_change3);
                        Collision_check collisionChecker4;
                        if (!collisionChecker4.checkCollision4(distances, new_sequence2, 0, alreadynum + 1, segArc, curvature))
                        {
                            std::vector<double> new_type2 = candidate.type;
                            new_type2.push_back(1);
                            double new_score2 = candidate.score + 1;
                            beam.push(State(new_sequence2, new_score2, new_type2));
                            type_1_ok = 1;
                            break;
                        }
                        double angle_change4 = angles[alreadynum] - i;
                        std::vector<double> new_sequence3 = candidate.sequence;
                        new_sequence3.push_back(angle_change4);
                        Collision_check collisionChecker5;
                        if (!collisionChecker5.checkCollision4(distances, new_sequence3, 0, alreadynum + 1, segArc, curvature))
                        {
                            std::vector<double> new_type3 = candidate.type;
                            new_type3.push_back(1);
                            double new_score3 = candidate.score + 1;
                            beam.push(State(new_sequence3, new_score3, new_type3));
                            type_1_ok = 1;
                            break;
                        }
                    }
                    //只改变自己不行 全部都改
                    if (!type_1_ok)
                    {
                        std::vector<double> new_type4 = candidate.type;
                        std::vector<double> open_point;
                        new_type4.push_back(1);
                        int count = 0;
                        for (int i = 0; i < new_type4.size(); i++) {
                            if (new_type4[i] == 1.0) {
                                open_point.push_back(i); // 记录满足条件的位置
                            }
                        }
                        count = open_point.size();
                        //改变所有开点（包括目前的）找到合适
                        //int limit = static_cast<int>(std::pow(150, count));
                        std::vector<double> new_sequence4 = candidate.sequence;
                        new_sequence4.push_back(angles[alreadynum]);
                        bool find_ok = 0;
                        auto start_try = std::chrono::high_resolution_clock::now();
                        for (int j = 0; j < count; j++)
                        {
                            for (int k = 0; k < 150; k++) {
                                Collision_check collisionChecker6;
                                new_sequence4[open_point[j]] += k;
                                if (!collisionChecker6.checkCollision4(distances, new_sequence4, 0, alreadynum + 1, segArc, curvature))
                                {
                                    double new_score4 = candidate.score + 1;
                                    beam.push(State(new_sequence4, new_score4, new_type4));
                                    find_ok = 1;
                                    break;
                                }
                                new_sequence4[open_point[j]] -= 2 * k;
                                Collision_check collisionChecker7;
                                if (!collisionChecker7.checkCollision4(distances, new_sequence4, 0, alreadynum + 1, segArc, curvature))
                                {
                                    double new_score41 = candidate.score + 1;
                                    beam.push(State(new_sequence4, new_score41, new_type4));
                                    find_ok = 1;
                                    break;
                                }
                                new_sequence4[open_point[j]] += k;
                            }
                            if (find_ok)
                            {
                                break;
                            }
                        }
                        if(count>1&&!find_ok)
                        {
                            for (int j = 0; j < count; j++)//改两个 01 
                            {
                                for (int j2 = j+1; j2 < count; j2++)
                                {
                                    for (int k = 0; k < 150; k++) {
                                        for (int t = 0; t < 150; t++)
                                        {
                                            Collision_check collisionChecker611;
                                            new_sequence4[open_point[j]] += k;
                                            new_sequence4[open_point[j2]] += t;
                                            if (!collisionChecker611.checkCollision4(distances, new_sequence4, 0, alreadynum + 1, segArc, curvature))
                                            {
                                                double new_score4 = candidate.score + 1;
                                                beam.push(State(new_sequence4, new_score4, new_type4));
                                                find_ok = 1;
                                                break;
                                            }
                                            new_sequence4[open_point[j]] -= 2*k;
                                            new_sequence4[open_point[j2]] -= 2*t;
                                            Collision_check collisionChecker711;
                                            if (!collisionChecker711.checkCollision4(distances, new_sequence4, 0, alreadynum + 1, segArc, curvature))
                                            {
                                                double new_score41 = candidate.score + 1;
                                                beam.push(State(new_sequence4, new_score41, new_type4));
                                                find_ok = 1;
                                                break;
                                            }
                                            new_sequence4[open_point[j]] += k;
                                            new_sequence4[open_point[j2]] += t;
                                        }
                                        if (find_ok)
                                        {
                                            break;
                                        }
                                    }
                                    if (find_ok)
                                    {
                                        break;
                                    }
                                }
                                if (find_ok)
                                {
                                    break;
                                }
                            }
                        }
                        if (count > 2 && !find_ok)
                        {
                            for (int j = 0; j < count; j++)//改两个 01 
                            {
                                for (int j2 = j + 1; j2 < count; j2++)
                                {
                                    for (int j3 = j2 + 1; j3 < count; j3++)
                                    {
                                        for (int k = 0; k < 150; k++) {
                                            for (int t = 0; t < 150; t++)
                                            {
                                                for(int t2 = 0; t2 < 150; t2++)
                                                {
                                                    Collision_check collisionChecker611;
                                                    new_sequence4[open_point[j]] += k;
                                                    new_sequence4[open_point[j2]] += t;
                                                    new_sequence4[open_point[j3]] += t2;
                                                    if (!collisionChecker611.checkCollision4(distances, new_sequence4, 0, alreadynum + 1, segArc, curvature))
                                                    {
                                                        double new_score4 = candidate.score + 1;
                                                        beam.push(State(new_sequence4, new_score4, new_type4));
                                                        find_ok = 1;
                                                        break;
                                                    }
                                                    new_sequence4[open_point[j]] -= 2 * k;
                                                    new_sequence4[open_point[j2]] -= 2 * t;
                                                    new_sequence4[open_point[j3]] -= 2 * t2;
                                                    Collision_check collisionChecker711;
                                                    if (!collisionChecker711.checkCollision4(distances, new_sequence4, 0, alreadynum + 1, segArc, curvature))
                                                    {
                                                        double new_score41 = candidate.score + 1;
                                                        beam.push(State(new_sequence4, new_score41, new_type4));
                                                        find_ok = 1;
                                                        break;
                                                    }
                                                    new_sequence4[open_point[j]] += k;
                                                    new_sequence4[open_point[j2]] += t;
                                                    new_sequence4[open_point[j3]] += t2;
                                                }
                                                if (find_ok)
                                                {
                                                    break;
                                                }
                                            }
                                            if (find_ok)
                                            {
                                                break;
                                            }
                                        }
                                        if (find_ok)
                                        {
                                            break;
                                        }
                                    }
                                    if (find_ok)
                                    {
                                        break;
                                    }
                                }
                                if (find_ok)
                                {
                                    break;
                                }
                            }
                        }
                        auto end_try = std::chrono::high_resolution_clock::now();
                        timeTry += end_try - start_try;
                    }

                    //type=0  //改变前面所有开点
                    std::vector<double> new_type5 = candidate.type;
                    new_type5.push_back(0);
                    int count2 = 0;
                    std::vector<double> open_point2;
                    for (int i = 0; i < new_type5.size(); i++)
                    {
                        if (new_type5[i] == 1.0) {
                            open_point2.push_back(i); // 记录满足条件的位置
                        }
                    }
                    count2 = open_point2.size();
                    //int limit2 = static_cast<int>(std::pow(150, count2));
                    std::vector<double> new_sequence5 = candidate.sequence;
                    new_sequence5.push_back(angles[alreadynum]);
                    bool find_ok2 = 0;
                    auto start_try2 = std::chrono::high_resolution_clock::now();
                    for (int j = 0; j < count2; j++)
                    {
                        for (int k = 0; k < 150; k++) {
                            Collision_check collisionChecker8;
                            new_sequence5[open_point2[j]] += k;
                            if (!collisionChecker8.checkCollision4(distances, new_sequence5, 0, alreadynum + 1, segArc, curvature))
                            {
                                double new_score5 = candidate.score;
                                beam.push(State(new_sequence5, new_score5, new_type5));
                                find_ok2 = 1;
                                break;
                            }
                            new_sequence5[open_point2[j]] -= 2 * k;
                            Collision_check collisionChecker9;
                            if (!collisionChecker9.checkCollision4(distances, new_sequence5, 0, alreadynum + 1, segArc, curvature))
                            {
                                double new_score51 = candidate.score;
                                beam.push(State(new_sequence5, new_score51, new_type5));
                                find_ok2 = 1;
                                break;
                            }
                            new_sequence5[open_point2[j]] += k;
                        }
                        if (find_ok2)
                        {
                            break;
                        }
                    }
                    if (count2 > 1 && !find_ok2)
                    {
                        for (int j = 0; j < count2; j++)//改两个 01 
                        {
                            for (int j2 = j + 1; j2 < count2; j2++)
                            {
                                for (int k = 0; k < 150; k++) {
                                    for (int t = 0; t < 150; t++)
                                    {
                                        Collision_check collisionChecker8;
                                        new_sequence5[open_point2[j]] += k;
                                        new_sequence5[open_point2[j2]] += t;
                                        if (!collisionChecker8.checkCollision4(distances, new_sequence5, 0, alreadynum + 1, segArc, curvature))
                                        {
                                            double new_score5 = candidate.score;
                                            beam.push(State(new_sequence5, new_score5, new_type5));
                                            find_ok2 = 1;
                                            break;
                                        }
                                        new_sequence5[open_point2[j]] -= 2 * k;
                                        new_sequence5[open_point2[j2]] -= 2 * t;
                                        Collision_check collisionChecker9;
                                        if (!collisionChecker9.checkCollision4(distances, new_sequence5, 0, alreadynum + 1, segArc, curvature))
                                        {
                                             double new_score51 = candidate.score;
                                             beam.push(State(new_sequence5, new_score51, new_type5));
                                             find_ok2 = 1;
                                             break;
                                        }
                                        new_sequence5[open_point2[j]] += k;
                                        new_sequence5[open_point2[j2]] += t;
                                    }
                                    if (find_ok2)
                                    {
                                        break;
                                    }
                                }
                                if (find_ok2)
                                {
                                    break;
                                }
                            }
                            if (find_ok2)
                            {
                                break;
                            }
                        }
                    }
                    if (count2 > 2 && !find_ok2)
                    {
                        for (int j = 0; j < count2; j++)//改两个 01 
                        {
                            for (int j2 = j + 1; j2 < count2; j2++)
                            {
                                for (int j3 = j2 + 1; j3 < count2; j3++)
                                {
                                    for (int k = 0; k < 150; k++) {
                                        for (int t = 0; t < 150; t++)
                                        {
                                            for (int t2 = 0; t2 < 150; t2++)
                                            {
                                                Collision_check collisionChecker8;
                                                new_sequence5[open_point2[j]] += k;
                                                new_sequence5[open_point2[j2]] += t;
                                                new_sequence5[open_point2[j3]] += t2;
                                                if (!collisionChecker8.checkCollision4(distances, new_sequence5, 0, alreadynum + 1, segArc, curvature))
                                                {
                                                    double new_score5 = candidate.score;
                                                    beam.push(State(new_sequence5, new_score5, new_type5));
                                                    find_ok2 = 1;
                                                    break;
                                                }
                                                new_sequence5[open_point2[j]] -= 2 * k;
                                                new_sequence5[open_point2[j2]] -= 2 * t;
                                                new_sequence5[open_point2[j3]] -= 2*t2;
                                                Collision_check collisionChecker9;
                                                if (!collisionChecker9.checkCollision4(distances, new_sequence5, 0, alreadynum + 1, segArc, curvature))
                                                {
                                                    double new_score51 = candidate.score;
                                                    beam.push(State(new_sequence5, new_score51, new_type5));
                                                    find_ok2 = 1;
                                                    break;
                                                }
                                                new_sequence5[open_point2[j]] += k;
                                                new_sequence5[open_point2[j2]] += t;
                                                new_sequence5[open_point2[j3]] += t2;
                                            }
                                            if (find_ok2)
                                            {
                                                break;
                                            }
                                        }
                                        if (find_ok2)
                                        {
                                            break;
                                        }
                                    }
                                    if (find_ok2)
                                    {
                                        break;
                                    }
                                }
                                if (find_ok2)
                                {
                                    break;
                                }
                            }
                            if (find_ok2)
                            {
                                break;
                            }
                        }
                    }
                    auto end_try2 = std::chrono::high_resolution_clock::now();
                    timeTry += end_try2 - start_try2;

                }
            }
        }
        finish_angle++;
        std::cout << finish_angle << " ";
    }

    // Sort and return the top-k results
    std::sort(result.begin(), result.end());
    std::cout << "ok" << std::endl;

    return result;
}
