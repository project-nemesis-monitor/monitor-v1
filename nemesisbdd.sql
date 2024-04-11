-- phpMyAdmin SQL Dump
-- version 5.2.1deb2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : jeu. 11 avr. 2024 à 12:56
-- Version du serveur : 10.11.6-MariaDB-2
-- Version de PHP : 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `nemesisbdd`
--

-- --------------------------------------------------------

--
-- Structure de la table `checkfile`
--

CREATE TABLE `checkfile` (
  `id` int(11) NOT NULL,
  `file_id` text NOT NULL,
  `filename` text NOT NULL,
  `check_mod` tinyint(1) NOT NULL,
  `path` text NOT NULL,
  `permissions` text DEFAULT NULL,
  `upload_by` text NOT NULL,
  `upload_at` timestamp NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `checkfile`
--

INSERT INTO `checkfile` (`id`, `file_id`, `filename`, `check_mod`, `path`, `permissions`, `upload_by`, `upload_at`) VALUES
(1, 'hhg4gg1', 'test2.txt', 1, '/home/virtuoso_vendetta/Bureau/monitor-v1/testother/test2.txt', '644', '301d1246-93bd-4e7f-b570-fd7fb2c4d2b1', '2024-04-05 07:37:31'),
(2, 'testbvh', 'xx.txt', 1, '/home/virtuoso_vendetta/Bureau/monitor-v1/xx.txt', '666', '301d1246-93bd-4e7f-b570-fd7fb2c4d2b1', '2024-04-05 07:37:37'),
(3, 'hhg4gg2', 'coucou.txt', 1, '/home/virtuoso_vendetta/Bureau/monitor-v1/coucou.txt', '644', '301d1246-93bd-4e7f-b570-fd7fb2c4d2b1', '2024-04-05 07:37:31');



--
-- Structure de la table `logs`
--

CREATE TABLE `logs` (
  `log_id` int(11) NOT NULL,
  `event_type` varchar(255) DEFAULT NULL,
  `event_description` text DEFAULT NULL,
  `file_id` text NOT NULL,
  `timestamp` timestamp NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `logs`
--

INSERT INTO `logs` (`log_id`, `event_type`, `event_description`, `file_id`, `timestamp`) VALUES
(1, 'permissions_change', 'Permissions changed: 644 => 640', 'hhg4gg1', '2024-04-05 17:16:49'),
(2, 'permissions_change', 'Permissions changed: 640 => 644', 'hhg4gg1', '2024-04-05 17:16:53'),
(3, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/testfile.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/ssl.txt', 'testbvh', '2024-04-06 11:03:25'),
(4, 'filename_change', 'Filename changed: testfile.txt => ssl.txt', 'testbvh', '2024-04-06 11:03:25'),
(5, 'permissions_change', 'Permissions changed: 644 => 0000', 'testbvh', '2024-04-06 11:20:56'),
(6, 'permissions_change', 'Permissions changed: 0000 => 777', 'testbvh', '2024-04-06 11:21:24'),
(7, 'permissions_change', 'Permissions changed: 777 => yyyy', 'testbvh', '2024-04-06 11:24:57'),
(8, 'permissions_change', 'Permissions changed: yyyy => 7777', 'testbvh', '2024-04-06 11:28:25'),
(9, 'permissions_change', 'Permissions changed: 7777 => 777', 'testbvh', '2024-04-06 11:37:16'),
(10, 'permissions_change', 'Permissions changed: 777 => 644', 'testbvh', '2024-04-06 11:37:31'),
(11, 'permissions_change', 'Permissions changed: 644 => 2644', 'testbvh', '2024-04-06 11:38:04'),
(12, 'permissions_change', 'Permissions changed: 2644 => 644', 'testbvh', '2024-04-06 11:38:22'),
(13, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/ssl.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/testfile.txt', 'testbvh', '2024-04-06 12:46:20'),
(14, 'filename_change', 'Filename changed: ssl.txt => testfile.txt', 'testbvh', '2024-04-06 12:46:20'),
(15, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/testother/likeme.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/testother/test2.txt', 'hhg4gg1', '2024-04-06 12:47:17'),
(16, 'filename_change', 'Filename changed: ggg55454 => test2.txt', 'hhg4gg1', '2024-04-06 12:47:23'),
(17, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/testfile.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/tet.txt', 'testbvh', '2024-04-06 13:29:47'),
(18, 'filename_change', 'Filename changed: testfile.txt => tet.txt', 'testbvh', '2024-04-06 13:29:47'),
(19, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/tet.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/test2.txt', 'testbvh', '2024-04-06 13:31:15'),
(20, 'filename_change', 'Filename changed: tet.txt => test2.txt', 'testbvh', '2024-04-06 13:31:15'),
(21, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/test2.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/testfile.txt', 'testbvh', '2024-04-06 13:35:10'),
(22, 'filename_change', 'Filename changed: test2.txt => testfile.txt', 'testbvh', '2024-04-06 13:35:20'),
(23, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/ff/tester.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/new.txt', '3', '2024-04-06 14:26:29'),
(24, 'filename_change', 'Filename changed: tester.txt => new.txt', '3', '2024-04-06 14:26:29'),
(25, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/new.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/xx.txt', '3', '2024-04-06 14:44:22'),
(26, 'filename_change', 'Filename changed: new.txt => xx.txt', '3', '2024-04-06 14:44:22'),
(27, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/xx.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/ff//home/virtuoso_vendetta/Bureau/monitor-v1/ff', '3', '2024-04-06 14:45:15'),
(28, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/ff//home/virtuoso_vendetta/Bureau/monitor-v1/ff => /home/virtuoso_vendetta/Bureau/monitor-v1/ff/ff.txt', '3', '2024-04-06 14:45:25'),
(29, 'filename_change', 'Filename changed: xx.txt => ff.txt', '3', '2024-04-06 14:45:33'),
(30, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/ff/ff.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/s.txt', '3', '2024-04-06 14:45:48'),
(31, 'filename_change', 'Filename changed: ff.txt => s.txt', '3', '2024-04-06 14:45:48'),
(32, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/s.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/ff/s.txt', '3', '2024-04-06 14:49:26'),
(33, 'filename_change', 'Filename changed: testfile.txt => xx.txt', '2', '2024-04-11 08:06:30'),
(34, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/testfile.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/xx.txt', '2', '2024-04-11 08:06:39'),
(35, 'permissions_change', 'Permissions changed: 644 => 666', '2', '2024-04-11 08:11:36'),
(36, 'filename_change', 'Filename changed: s.txt => test.txt', '3', '2024-04-11 08:24:28'),
(37, 'filename_change', 'Filename changed: test.txt => s.txt', '3', '2024-04-11 08:24:41'),
(38, 'path_change', 'Path changed: /home/virtuoso_vendetta/Bureau/monitor-v1/ff/s.txt => /home/virtuoso_vendetta/Bureau/monitor-v1/coucou.txt', '3', '2024-04-11 09:23:55'),
(39, 'filename_change', 'Filename changed: s.txt => coucou.txt', '3', '2024-04-11 09:23:55');

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `user_id` text NOT NULL,
  `username` varchar(255) NOT NULL,
  `email` text NOT NULL,
  `role` varchar(255) NOT NULL,
  `password` text NOT NULL,
  `token` text NOT NULL,
  `remember_token` text DEFAULT NULL,
  `refresh_token_time` datetime DEFAULT NULL,
  `created_at` datetime(3) NOT NULL DEFAULT current_timestamp(3),
  `updated_at` datetime(3) DEFAULT current_timestamp(3)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `users`
--

INSERT INTO `users` (`id`, `user_id`, `username`, `email`, `role`, `password`, `token`, `remember_token`, `refresh_token_time`, `created_at`, `updated_at`) VALUES
(1, '301d1246-93bd-4e7f-b570-fd7fb2c4d2b1', 'root', 'root@example.com', 'super admin', '$2b$10$oJdQoaQaFSeO7oHeOk06VelqqBKDcWSbFBi3BPHJxm31J8SoH8Xma', 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOiIzMDFkMTI0Ni05M2JkLTRlN2YtYjU3MC1mZDdmYjJjNGQyYjEiLCJpYXQiOjE3MTE3MDI2Mzd9.YRDQTtJEVVffs6CMo63ke5e28REOQXTyJoNSJ6Pks5w', NULL, NULL, '2024-03-29 08:57:17.299', '2024-03-29 08:57:17.299');

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `checkfile`
--
ALTER TABLE `checkfile`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `logs`
--
ALTER TABLE `logs`
  ADD PRIMARY KEY (`log_id`);

--
-- Index pour la table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `checkfile`
--
ALTER TABLE `checkfile`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT pour la table `logs`
--
ALTER TABLE `logs`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=40;

--
-- AUTO_INCREMENT pour la table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;


--
-- Déclencheurs `checkfile`
--
DELIMITER //
CREATE TRIGGER `file_change_trigger` AFTER UPDATE ON `checkfile` FOR EACH ROW BEGIN
    IF NEW.path != OLD.path THEN
        INSERT INTO logs (event_type, event_description, file_id)
        VALUES ('path_change', CONCAT('Path changed: ', OLD.path, ' => ', NEW.path), OLD.id) DELIMITER ;
DELIMITER //        
CREATE TRIGGER `file_delete_trigger` AFTER DELETE ON `checkfile` FOR EACH ROW BEGIN
    INSERT INTO logs (event_type, event_description) VALUES ('file_deleted', CONCAT('File deleted: ', OLD.path)) DELIMITER ;
DELIMITER //
CREATE TRIGGER `file_insert_trigger` AFTER INSERT ON `checkfile` FOR EACH ROW BEGIN
    INSERT INTO logs (event_type, event_description) VALUES ('file_inserted', CONCAT('New file inserted: ', NEW.path)) DELIMITER ;

-- --------------------------------------------------------

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
